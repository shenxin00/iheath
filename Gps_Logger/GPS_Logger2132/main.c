#include <msp430x21x2.h>

#define CHECK_DATA_VALID			1

#define FLASH_DATA_START_ADDR		0x000000
#define FLASH_DATA_END_ADDR			0x05FFFF
#define FLASH_CONFIG_ADDR			0x06C000
#define FLASH_CONFIG_SIZE			0x08
#define FIRST_START_FLG				0xAA
#define FLASH_OVER_FLG				0xBB

#define OPCODE_ERASE_4K				0x20
#define OPCODE_ERASE_32K			0x52
#define OPCODE_ERASE_64K			0xD8

#define DATA_BUF_SIZE				128

#define CHAR_LF						0x0A
#define CHAR_CR						0x0D


/*
*	byte 0		FIRST_START_FLG: 0xAA 
*	byte 1		cur_data_addr
*	byte 2		cur_data_addr
*	byte 3		cur_data_addr MSB
*	byte 4		FLASH_OVER_FLG：0xBB
*	byte 5		data_cnt
*	byte 6		data_cnt
*	byte 7		data_cnt  MSB
*/

#define OK							1
#define ERR							0

//data buf
unsigned char data_buf[128];
unsigned char data_cnt;
unsigned char gps_recive_status;
//flash 
unsigned char flash_status;
unsigned char flash_over_status;
unsigned long cur_data_addr;
unsigned long cur_data_cnt;


unsigned char USER_CTL=0;
void delay(unsigned int t);
void CLK_Init(void);
void USCIB0_putch(unsigned char _Byte);
unsigned char USCIB0_getch(void);
void flash_init(void);
void flash_write_data(unsigned long _addr,unsigned char* _str,unsigned char _size);
void flash_read_data(unsigned long _addr,unsigned char *_str,unsigned char _size);
unsigned char get_flash_status(void);
void flash_wait_busy(void);
void flash_erase_block(unsigned char _op,unsigned long _addr);
void flash_erase_chip(void);
void flash_power_on(void);
void flash_power_down(void);
void USCIA0_Init(void);
void USCIA0_putch(unsigned char _Byte);
unsigned char USCIA0_getch(void);
void uart_write_data(unsigned char* _data, unsigned char _size);
void TimerA_Init(void);
unsigned char gps_recv_data(unsigned char _cnt);
unsigned char dec2hex(unsigned char dec);
unsigned char hex2dec(unsigned char hex);
void usb_send_data(void);
void reset_data_buf(void);

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=100;x>0;x--)
		for(y=t;y>0;y--);
	return;
}

void CLK_Init(void)
{
	// 设置DCO频率为12M..
	BCSCTL1 = CALBC1_1MHZ; 
	DCOCTL  = CALDCO_1MHZ;

	// 选择DCO作为MCLK时钟(默认）..

	// 对内部VLOCLK 8分频作为ACLK时钟..
	BCSCTL1 |= DIVA_3;
	BCSCTL3 |= LFXT1S1;

	// DCO 不分频作为SMCLK(默认）..

	return;
}
void TimerA_Init(void)
{  
  /* 12k/8/8 = 187.5Hz */
  /* 设定定时期器(0xFFFF = 65535)	*/
  /* 10s	= 187.5*10 = 1875		*/
  /* 30s	= 187.5*30 = 5625		*/
  /* 300s	= 5625*10  = 56250		*/
  // TA0CCR0 = 5120;
  TACCR0 = 187;
  TACTL = TASSEL_1 + ID_3 + MC_1 + TAIE;		   // ACLK, 8div, contmode, interrupt
  
  return;
}

/////////////////////////////////////////////
//	P3.1	SPI_MO	 OUT
//	P3.2	SPI_MI	 IN
//	P3.3	SPI_CLK  OUT
//	P2.3	/CS 	 OUT
//	P2.4	/WP 	 OUT
/////////////////////////////////////////////
void USCIB0_putch(unsigned char _Byte)
{
	while(!(IFG2&UCB0TXIFG));
	UCB0TXBUF = _Byte;
	while (!(IFG2&UCB0RXIFG));			// USCI_B0 RX buffer ready?
	_Byte = UCB0RXBUF;					// clear the dumy byte
	return;
}

unsigned char USCIB0_getch(void)
{
	while(!(IFG2&UCB0TXIFG));
	UCB0TXBUF = 0x00;						// for create recive clock
	while (!(IFG2&UCB0RXIFG));			// USCI_B0 RX buffer ready?
	return UCB0RXBUF;
}

void flash_init(void)
{
	unsigned char _buf[FLASH_CONFIG_SIZE];
	P3SEL |= 0x0E;									// P3.3,2,1 USCI_B0 option select
	UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;	// 3-pin, 8-bit SPI mstr, MSB 1st SPi mode 0
	UCB0CTL1 |= UCSSEL_2; 							// SMCLK
	UCB0BR0 = 0x02;
	UCB0BR1 = 0x00;
	delay(100);

	UCB0CTL1 &= ~UCSWRST; 					// **Initialize USCI state machine**
	delay(200);
 
	// /WP /CS config
	P2DIR |= 0x18;							// P2.3 P2.4  output direction
	P2OUT |= 0x08;							// P2.3 = CS = 1 disable AT25DFXXX /CS set
	P2OUT |= 0x10;							// P2.4 = WP = 1 disable WP   /WP set
	delay(2);
	// flash power on mode
	flash_power_on();
	delay(200);
                
	//Write Enable
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x06);						// Opcode
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop read /CS set
	delay(2);

	//Global Unprotect all data sectors
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x01);						// Opcode
	USCIB0_putch(0x00);						// status Register data
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop read /CS set
	delay(2);
	  
	//Read Status Register
        get_flash_status();

        
//debug
//flash_erase_chip();
   

	//Read config information
	flash_read_data(FLASH_CONFIG_ADDR,_buf,FLASH_CONFIG_SIZE);
	if(_buf[0] != FIRST_START_FLG)
	{
		cur_data_addr = FLASH_DATA_START_ADDR;
		cur_data_cnt  = 0;
		flash_erase_chip();
	}
	else
	{
		cur_data_addr = (_buf[1]<<16) + (_buf[2]<<8) + (_buf[3]);
		flash_over_status = _buf[4];
		cur_data_cnt  = (_buf[5]<<16) + (_buf[6]<<8) + (_buf[7]);
	}

	return;
}

void flash_write_data(unsigned long _addr,unsigned char* _data,unsigned char _size)
{
	unsigned char addr[3];
	addr[2] = (_addr>>16)&0xFF;
	addr[1] = (_addr>>8)&0xFF;
	addr[0] = (_addr)&0xFF;

	//Write Enable
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x06);						// Opcode
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop read /CS set
	delay(2);

	//write data to AT25DFXXX
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start write /CS reset		 
	USCIB0_putch(0x02);						// Opcode
	USCIB0_putch(addr[2]);					// Address Bytes
	USCIB0_putch(addr[1]);					// Address Bytes
	USCIB0_putch(addr[0]);					// Address Bytes
	// data to write 
	while(_size > 0)
	{
		USCIB0_putch(*_data++);				// data Bytes
		_size--;
	}
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop write AT25DFXXX /CS set
	delay(2);
        
	// write over
	while(get_flash_status()&BIT0);           //wait until not busy
	
	return; 
}

void flash_read_data(unsigned long _addr,unsigned char *_data,unsigned char _size)
{
	unsigned char addr[3];
	addr[2] = (_addr>>16)&0xFF;
	addr[1] = (_addr>>8)&0xFF;
	addr[0] = (_addr)&0xFF;

	//read data from AT25DFXXX
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start read /CS reset 
	USCIB0_putch(0x0B);						// Opcode
	USCIB0_putch(addr[2]);					// Address Bytes
	USCIB0_putch(addr[1]);					// Address Bytes
	USCIB0_putch(addr[0]);					// Address Bytes
	USCIB0_putch(0x00);						// Dummy Bytes
	while(_size > 0 )
	{
	  *_data++ = USCIB0_getch();			// data Bytes
	  _size--;
	}
	//stop the string
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop read /CS set	  
	delay(2);
	while(get_flash_status()&BIT0);			//wait until not busy
}
unsigned char get_flash_status(void)
{
	//Read Status Register
	P2OUT &= ~0x08;							// P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x05);						// Opcode
	flash_status = USCIB0_getch();			                // status Register data
	P2OUT |= 0x08;							// P2.3 = CS = 1 stop read /CS set
	delay(2);
	return flash_status;
}

void flash_erase_chip(void)
{        
	//Write Enable
	P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x06);                       // Opcode
	P2OUT |= 0x08;                            // P2.3 = CS = 1 stop read /CS set
	delay(2);   
	//block Erase
	P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
	USCIB0_putch(0x60);                       // Opcode
	P2OUT |= 0x08;                            // P2.3 = CS = 1 stop read /CS set
	delay(2);   

	while(get_flash_status()&BIT0);           //wait until not busy

	return; 
}

void flash_power_down(void)
{        
        // flash_power_down
        P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
        USCIB0_putch(0xB9);                       // Opcode
        P2OUT |= 0x08;                            // P2.3 = CS = 1 stop read /CS set
        delay(20);         
        return; 
}

void flash_power_on(void)
{        
        // flash_power_down
        P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
        USCIB0_putch(0xAB);                       // Opcode
        P2OUT |= 0x08;                            // P2.3 = CS = 1 stop read /CS set
        delay(10);        
        while(!(get_flash_status()&BIT4));                         //wait 

        return; 
}

void flash_erase_block(unsigned char _op,unsigned long _addr)
{
  	unsigned char addr[3];
	addr[2] = (_addr>>16)&0xFF;
	addr[1] = (_addr>>8)&0xFF;
	addr[0] = (_addr)&0xFF;
        
        //Write Enable
        P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
        USCIB0_putch(0x06);                       // Opcode
        P2OUT |= 0x08;                           // P2.3 = CS = 1 stop read /CS set
        delay(2);   
        //block Erase
        P2OUT &= ~0x08;                           // P2.3 = CS = 0 start read /CS reset
        USCIB0_putch(_op);                        // Opcode
        USCIB0_putch(addr[2]);                    // Address Bytes
        USCIB0_putch(addr[1]);                    // Address Bytes
        USCIB0_putch(addr[0]);                    // Address Bytes
        P2OUT |= 0x08;                            // P2.3 = CS = 1 stop read /CS set
        delay(2);   
        
        while(get_flash_status()&BIT0);           //wait until not busy
        
        return; 
}

void USCIA0_Init(void)
{
	/* P3.4、P3.5为UTXD1、URXD1 */
	P3SEL |= 0x30; 							// P3.4,5 = USCI_A0 TXD/RXD
	/* default config		*/
	/* Async. Mode: Parity disable */
	/* Async. Mode: Parity	   0:odd / 1:even */
	/* Async. Mode: MSB first  0:LSB / 1:MSB */
	/* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
	/* Async. Mode: Stop Bits  0:one / 1: two */

	UCA0CTL1 |= UCSSEL_2; 					        // CLK = SMCLK 1MHz
	UCA0BR0 = 208;							// 1MHz 4800
	UCA0BR1 = 0;							// 1MHz 4800
	UCA0MCTL = UCBRS0;						// Modulation 0 	 

	UCA0CTL1 &= ~UCSWRST; 					// **Initialize USCI state machine**/

	/* Delay */
	delay(100);

}

void USCIA0_putch(unsigned char _Byte)
{
	while(!(IFG2&UCA0TXIFG));
	UCA0TXBUF =_Byte;
	
	return;
}

void uart_write_data(unsigned char* _data, unsigned char _size)
{
	while(_size > 0)
	{
		USCIA0_putch(*_data);
		_data++;
		_size--;
	}
	return;
}


unsigned char USCIA0_getch(void){
	unsigned char temp=0;
	while(temp == 0)
	{
		while(!(IFG2&UCA0RXIFG));		// USCI_A0 RX buffer ready?
		temp = UCA0RXBUF;
	}
	return temp;
}

unsigned char gps_recv_data(unsigned char _cnt)
{
	unsigned char recv_cnt=0;
	unsigned char temp=0;
	unsigned char checksum=0;
	unsigned char i;
	unsigned char hex_H,hex_L;
                
	//on  _cnt == 0 trap the mcu until get (vaild) gps data
	while((recv_cnt < _cnt)||(_cnt == 0))
	{	 

                //reset data buf to 0
		reset_data_buf();
                
		if((temp = USCIA0_getch()) != '$') continue;
		data_buf[data_cnt++] = temp;
		if((temp = USCIA0_getch()) != 'G') continue;
		data_buf[data_cnt++] = temp;
		if((temp = USCIA0_getch()) != 'P') continue;
		data_buf[data_cnt++] = temp;
		if((temp = USCIA0_getch()) != 'R') continue;
		data_buf[data_cnt++] = temp;
		if((temp = USCIA0_getch()) != 'M') continue;
		data_buf[data_cnt++] = temp;
		if((temp = USCIA0_getch()) != 'C') continue;
		data_buf[data_cnt++] = temp;
		
		while((temp = USCIA0_getch()) != '*')
		{
			data_buf[data_cnt++] = temp;
		}
		//*
		data_buf[data_cnt++] = temp;
		//get checksum
		data_buf[data_cnt++] = USCIA0_getch();
		data_buf[data_cnt++] = USCIA0_getch();
		// LR CF
		data_buf[data_cnt++] = USCIA0_getch();
		data_buf[data_cnt++] = USCIA0_getch();

		//check checksum
		checksum = 0;
		for(i=1;i<data_cnt-5;i++)
		{
			checksum ^= data_buf[i];
		}

		hex_H = dec2hex(checksum/16);
		hex_L = dec2hex(checksum - hex_H*16);

		if((hex_H != data_buf[data_cnt-4])||(hex_L != data_buf[data_cnt-3]))
		{
			recv_cnt++;
			continue;
		}
                
#if CHECK_DATA_VALID
		//check data valid 
		//$GPRMC,151229.487,A,3723.2475,N,12148.3416,W,0.13,309.62,120598,,,A*5F
		if(data_buf[18] != 'A' )
		{
			recv_cnt++;
			continue;
		}
#endif
		return OK;
	}
	
	return ERR;

}

void save_data(unsigned char* _data,unsigned char _size)
{
	unsigned char _buf[FLASH_CONFIG_SIZE];
	unsigned char temp_size;
	
	if(cur_data_addr+_size > FLASH_DATA_END_ADDR)
	{
		cur_data_addr = FLASH_DATA_START_ADDR;
		flash_over_status = FLASH_OVER_FLG;
	}

	temp_size = 256 - cur_data_addr&0xFF;
	if(_size > temp_size)
	{
		flash_write_data(cur_data_addr,_data,temp_size);
		flash_write_data(cur_data_addr+temp_size,_data+temp_size,_size-temp_size);
	}
	else
	{
		flash_write_data(cur_data_addr,_data,_size);
	}
	cur_data_addr += _size;
	cur_data_cnt++;

	_buf[0] = FIRST_START_FLG;
	_buf[1] = (cur_data_addr>>16)&0xFF;
	_buf[2] = (cur_data_addr>>8)&0xFF;
	_buf[3] = (cur_data_addr)&0xFF;
	_buf[4] = flash_over_status;
	_buf[5] = (cur_data_cnt>>16)&0xFF;
	_buf[6] = (cur_data_cnt>>8)&0xFF;
	_buf[7] = (cur_data_cnt)&0xFF;
	//erase config block
	flash_erase_block(OPCODE_ERASE_4K,FLASH_CONFIG_ADDR);
	//update config block
	flash_write_data(FLASH_CONFIG_ADDR,_buf,FLASH_CONFIG_SIZE);	

        
//debug	
//usb_send_data();
      return;
}

void usb_send_data(void)
{
	unsigned char read_cnt;
	unsigned char left;
	unsigned long end_data_addr;
        unsigned long read_addr;
	
	if(flash_over_status == FLASH_OVER_FLG)
	{
		end_data_addr = FLASH_DATA_END_ADDR;
	}
	else
	{
		end_data_addr = cur_data_addr;
	}
	
	read_cnt = (end_data_addr - FLASH_DATA_START_ADDR)/DATA_BUF_SIZE;
	left = (end_data_addr - FLASH_DATA_START_ADDR) - read_cnt*DATA_BUF_SIZE;
	
	read_addr = FLASH_DATA_START_ADDR;
	while(read_cnt>0)
	{
                //reset data buf to 0
		reset_data_buf();
		//read data from flash 
		flash_read_data(read_addr,data_buf,DATA_BUF_SIZE);
		read_addr += DATA_BUF_SIZE;
		read_cnt--;
		//wirte to usb port
		uart_write_data(data_buf,DATA_BUF_SIZE);
		
	}
        //reset data buf to 0
        reset_data_buf();
	//read data from flash 
	flash_read_data(read_addr,data_buf,left);
	//wirte to usb port
	uart_write_data(data_buf,left);
	
	return;
}

int main(void)
{
 
	WDTCTL = WDTPW + WDTHOLD; //关闭看门狗
	// all i/o port output direction
#if 0
	P1DIR = 0xFF;
	P2DIR = 0xFF;
	P3DIR = 0xFF;
	// all i/o output 0
	P1OUT = 0x00;
	P1OUT = 0x00;
	P1OUT = 0x00;	
#endif        
	//config LED
	P3DIR |= BIT7;
	//LED OFF
	P3OUT |= BIT7;

	//config mode select port
	P1DIR &= ~BIT1;

	/* default all interrupt disabled */
	/* config system clock */
	CLK_Init();
	delay(200);
	
	/* config USCI B0 for dataflash AT25DFXXX */
	flash_init();
	if(flash_status != 0x10){
		// on error trap the mcu..
		while(1);
	}


	/* config USCI A0 for GPS module */
	USCIA0_Init();
	delay(200);
                
	// mode select
	// GPS Recive mode P1.1 HIGH
	if(P1IN&BIT1){
		//config gps en port P3.6 
		P3DIR |= BIT6; 
		//OPEN GPS
		P3OUT &= ~BIT6;
		delay(200);
		
		//wait until recive vaild data from gps..
		if( gps_recv_data(0) == ERR)
                {
                  //trap the mcu 
                  while(1);
                }
		//write data to flash
		save_data(data_buf,data_cnt);
		
		// config Timer_A 
		TimerA_Init();		 
		// CLOSE GPS
		P3OUT |= BIT6;
		// flash power down mode
		flash_power_down();
		//config mode select port output mode 
		P1DIR |= BIT1;
		
		// Enter LPM0 w/ interrupt
		__bis_SR_register(LPM3_bits + GIE);
		
	}else{
		// USB output mode P1.1 LOW	
		while(1)
		{
                        USER_CTL = USCIA0_getch();
                        
			if(USER_CTL == 'A')
			{
				usb_send_data();
			}
                        if(USER_CTL == 'B')
                        {
                                flash_erase_chip();
                        }
		}

	}
	
	/* trap the mcu */
	while(1);
	 
}


//TIMER_A中断服务程序
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A (void)
{
	if( TAIV != 0x0A)
	{
		return;
	}
	TACTL &=~MC0;	//停止计数
	TACTL &=~MC1;	//停止计数
	
	//OPEN GPS
	P3OUT &= ~BIT6;
	//flash power on mode
	flash_power_on();
	// open led 
	P3OUT &= ~BIT7;

	delay(200);
	gps_recive_status = gps_recv_data(50);
	//CLOSE GPS
	P3OUT |= BIT6;

	if( gps_recive_status == OK)
	{
		//write data to flash
		save_data(data_buf,data_cnt);
	}
	//flash power down
	flash_power_down();

	//增计数模式开始计时
	TACTL |= MC_1;
	//close led
	P3OUT |= BIT7;
	
	return;
}


unsigned char dec2hex(unsigned char dec)
{
	if(dec > 9)
	{
		return dec+87;
	}
	else
	{
		return dec+48;
	}
}
unsigned char hex2dec(unsigned char hex)
{
	return 0;
}

void reset_data_buf(void)
{
  unsigned char i;
  //reset data buff to 0
  for(i=0;i<DATA_BUF_SIZE;i++)
  {
    data_buf[i] = 0;
  }
  data_cnt = 0;
  return;
}



