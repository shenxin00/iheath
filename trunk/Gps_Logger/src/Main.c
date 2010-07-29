#include <msp430x14x.h>
#include "system.h"
#include "mmc.h"
#include "znfat.h"
#include "string.h"
//#include <stdio.h>

struct FAT32_Init_Arg Init_Arg_Mmc;	   //初始化参数结构体实体
struct FileInfoStruct FileInfo; 	   //文件信息结构体实体
struct FAT32_Init_Arg *pArg=&Init_Arg_Mmc;
unsigned char Dev_No=0;
unsigned char Create_DT[6]={0x09,0x07,0x0d,0x0d,0x14,0x0f}; //日期时间 09年07月0d日0d时14分0f秒

unsigned long cardSize = 0;
unsigned char status = 1;
unsigned int timeout = 0;
int i = 0;







int main( void )
{
	//Initialisation of the WDT+
	WDTCTL = WDTPW + WDTHOLD;
	
	/********************************************************/
	/* Initialisation of the System Clock/GIO
	/* LFXT1CLK = 8MHz oscillator (Work in HF mode)
	/* VLOCLK   = 12 kHz
	/* ■ON Sleep Mode:
	/* Set LFXT1CLK As MCLK,SMCLK,ACLK
	/* ■ON Run Mode
	/* Set VLOCLK As VLOCLK,VLOCLK
	/********************************************************/
	
	/* 
	■BCSCTL1, Basic Clock System Control Register 1
	
	XT2OFF	Bit 7		XT2 off. This bit turns off the XT2 oscillator
							0 XT2 is on
							1 XT2 is off if it is not used for MCLK or SMCLK.
	XTS		Bit 6		LFXT1 mode select.
							0 Low frequency mode
							1 High frequency mode
	DIVAx	Bits 5-4	Divider for ACLK
							00 /1
							01 /2
							10 /4
							11 /8
	RSELx	Bits 3-0	Range Select. Sixteen different frequency ranges are available. The lowest
						frequency range is selected by setting RSELx=0. RSEL3 is ignored when DCOR = 1.
	
	■BCSCTL2, Basic Clock System Control Register 2
	SELMx	Bits 7-6	Select MCLK. These bits select the MCLK source.
							00 DCOCLK
							01 DCOCLK
							10 XT2CLK when XT2 oscillator present on-chip. LFXT1CLK or VLOCLK when XT2 oscillator not present on-chip.
							11 LFXT1CLK or VLOCLK
	DIVMx	Bits 5-4	Divider for MCLK
							00 /1
							01 /2
							10 /4
							11 /8
	SELS	Bit 3		Select SMCLK. This bit selects the SMCLK source.
							0 DCOCLK
							1 XT2CLK when XT2 oscillator present. LFXT1CLK or VLOCLK when XT2 oscillator not present
	DIVSx	BitS 2-1	Divider for SMCLK
							00 /1
							01 /2
							10 /4
							11 /8
	DCOR	Bit 0 		DCO resistor select
							0 Internal resistor
							1 External resistor

	■BCSCTL3, Basic Clock System Control Register 3
	
	XT2Sx	Bits7-6		XT2 range select. These bits select the frequency range for XT2.
							00 0.4 - 1-MHz crystal or resonator
							01 1 - 3-MHz crystal or resonator
							10 3 - 16-MHz crystal or resonator
							11 Digital external 0.4 ? 16-MHz clock source
	LFXT1Sx	Bits5-4		Low-frequency clock select and LFXT1 range select. These bits select
						between LFXT1 and VLO when XTS = 0, and select the frequency range for LFXT1 when XTS = 1.
							When XTS = 0:
							00 32768 Hz Crystal on LFXT1
							01 Reserved
							10 VLOCLK (Reserved in MSP430x21x1 devices)
							11 Digital external clock source
							When XTS = 1 (Not applicable for MSP430x20xx devices)
							00 0.4 - 1-MHz crystal or resonator
							01 1 - 3-MHz crystal or resonator
							10 3 - 16-MHz crystal or resonator
							11 Digital external 0.4 ? 16-MHz clock source
	XCAPx	Bits3-2		Oscillator capacitor selection. These bits select the effective capacitance
						seen by the LFXT1 crystal when XTS = 0. If XTS = 1 or if LFCT1Sx = 11 XCAPx should be 00.
							00 ~1 pF
							01 ~6 pF
							10 ~10 pF
							11 ~12.5 pF
	XT2OF	Bit 1 		XT2 oscillator fault
							0 No fault condition present
							1 Fault condition present
	LFXT1OF	Bit 0		LFXT1 oscillator fault
							0 No fault condition present
							1 Fault condition present	
	
	*/
	
	/*
	■BCSCTL1, Basic Clock System Control Register 1
	Run Mode:1111 0000
		XT2 is off
		LFXT1 High frequency mode
		8 Divider for ACLK
		The lowest frequency range
	
	Sleep Mode:1011 0000
		XT2 is off
		LFXT1 Low frequency mode
		8 Divider for ACLK
		The lowest frequency range

	
						
	XT2OFF	Bit 7		XT2 off. This bit turns off the XT2 oscillator
							0 XT2 is on
							1 XT2 is off if it is not used for MCLK or SMCLK.
	XTS		Bit 6		LFXT1 mode select.
							0 Low frequency mode
							1 High frequency mode
	DIVAx	Bits 5-4	Divider for ACLK
							00 /1
							01 /2
							10 /4
							11 /8
	RSELx	Bits 3-0	Range Select. Sixteen different frequency ranges are available. The lowest
						frequency range is selected by setting RSELx=0. RSEL3 is ignored when DCOR = 1.
	
	■BCSCTL2, Basic Clock System Control Register 2
	1100 1110
	LFXT1CLK or VLOCLK for MCLK source.
	1 Divider for MCLK
	LFXT1CLK or VLOCLK for SMCLK source.
	8 Divider for SMCLK
	DCO Internal resistor
	
	SELMx	Bits 7-6	Select MCLK. These bits select the MCLK source.
							00 DCOCLK
							01 DCOCLK
							10 XT2CLK when XT2 oscillator present on-chip. LFXT1CLK or VLOCLK when XT2 oscillator not present on-chip.
							11 LFXT1CLK or VLOCLK
	DIVMx	Bits 5-4	Divider for MCLK
							00 /1
							01 /2
							10 /4
							11 /8
	SELS	Bit 3		Select SMCLK. This bit selects the SMCLK source.
							0 DCOCLK
							1 XT2CLK when XT2 oscillator present. LFXT1CLK or VLOCLK when XT2 oscillator not present
	DIVSx	BitS 2-1	Divider for SMCLK
							00 /1
							01 /2
							10 /4
							11 /8
	DCOR	Bit 0 		DCO resistor select
							0 Internal resistor
							1 External resistor

	■BCSCTL3, Basic Clock System Control Register 3
	Run Mode:0010 00
		XT2 range select(Not use)
		LFXT1 range 3 - 16-MHz crystal 
		Oscillator capacitor selection(Not Use)
	Sleep Mode:0010 00
		XT2 range select(Not use)
		Low-frequency clock select VLOCLK
		Oscillator capacitor selection(Not Use)	
	
	XT2Sx	Bits7-6		XT2 range select. These bits select the frequency range for XT2.
							00 0.4 - 1-MHz crystal or resonator
							01 1 - 3-MHz crystal or resonator
							10 3 - 16-MHz crystal or resonator
							11 Digital external 0.4 - 16-MHz clock source
	LFXT1Sx	Bits5-4		Low-frequency clock select and LFXT1 range select. These bits select
						between LFXT1 and VLO when XTS = 0, and select the frequency range for LFXT1 when XTS = 1.
							When XTS = 0:
							00 32768 Hz Crystal on LFXT1
							01 Reserved
							10 VLOCLK (Reserved in MSP430x21x1 devices)
							11 Digital external clock source
							When XTS = 1 (Not applicable for MSP430x20xx devices)
							00 0.4 - 1-MHz crystal or resonator
							01 1 - 3-MHz crystal or resonator
							10 3 - 16-MHz crystal or resonator
							11 Digital external 0.4 ? 16-MHz clock source
	XCAPx	Bits3-2		Oscillator capacitor selection. These bits select the effective capacitance
						seen by the LFXT1 crystal when XTS = 0. If XTS = 1 or if LFCT1Sx = 11 XCAPx should be 00.
							00 ~1 pF
							01 ~6 pF
							10 ~10 pF
							11 ~12.5 pF
	XT2OF	Bit 1 		XT2 oscillator fault
							0 No fault condition present
							1 Fault condition present
	LFXT1OF	Bit 0		LFXT1 oscillator fault
							0 No fault condition present
							1 Fault condition present	
	
	*/
	
	
	/*
	Run Mode:1111 0000
		XT2 is off
		LFXT1 High frequency mode
		8 Divider for ACLK
		The lowest frequency range

	1100 1110
	LFXT1CLK or VLOCLK for MCLK source.
	1 Divider for MCLK
	LFXT1CLK or VLOCLK for SMCLK source.
	8 Divider for SMCLK
	DCO Internal resistor

	Run Mode:0010 00
		XT2 range select(Not use)
		LFXT1 range 3 - 16-MHz crystal 
		Oscillator capacitor selection(Not Use)
	*/
	
	BCSCTL1 = 11110000b;
	BCSCTL2 = 11001110b;
	BCSCTL3 = 00100000b;

LOOP:
	BCSCTL1&=~BIT7;		//打开外部12M晶振
	IFG1&=~BIT1;		//清除OFIFG
	delay(50);
	while(IFG1&BIT1){
		delay(50);
	}
	//Initialisation of the FLASH Memory


	//Initialisation of the GPS receiver
	//Open GPS receiver
	GPS_EN = ON;

	//Close GPS receiver
	GPS_EN = ON;
	
	//Initialisation of the Timer_A
	TIMER_A_Init();
	
	
	while (1);

	return;
	
}


void CLK_Init(void)
{
	unsigned char i;
	
}


unsigned char delay_flag=0;
void TIMER_A_Init(void)
{
	//选择ACLK作为时钟源，8分频（即12kHZ/8/8 = 187.5Hz）,增计数模式,停止计数
	TACTL=0x0200;
	TACCTL0=CCIE;
	_BIS_SR(GIE);
}

unsigned long DATA_ADDR = 0;

unsigned char CHECK_SUM;
unsigned char SLEEP_CNT;
unsigned char ERROR_CNT;
unsigned char CHAR_BUFF;
unsigned char GPS_BUFF[128];
unsigned char *GPS_BUFF_P;

//TIMER_A中断服务程序
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	//停止计数
	TACTL&=~BIT4;
	
	//数据获取间隔检查
	if(SLEEP_CNT <= XXX)
	{
		//数据获取间隔未到达
		SLEEP_CNT++;
		return;
	}
	
	//取数据条件
	//1,上次获取数据失败
	//2,数据获取间隔到达

	//启动GPS
	GPS_EN = ON;
		
	//!Todo切换时钟
	// VLOCK -> LFXT1 HF Mode
	
	

	
	CHAR_BUFF = 0;
	GPS_BUFF_P = GPS_BUFF;
	//读取GPS输出信息
	ERROR_CNT = 0;
	while(ERROR_CNT < 10)
	{
		//消息头检查
		if(USART_Receive()!='$') continue;
		ERROR_CNT++;
		if(USART_Receive()!='G') continue;
		if(USART_Receive()!='P') continue;
		if(USART_Receive()!='R') continue;
		if(USART_Receive()!='M') continue;
		if(USART_Receive()!='C') continue;

		//接收消息体

		while(CHAR_BUFF != 'LF')
		{		
			CHAR_BUFF = USART_Receive();
			*GPS_BUFF_P = CHAR_BUFF;
			GPS_BUFF_P++;
		}
		*GPS_BUFF_P = 0;
		
		//GPS消息接收完毕
		break;
	}
	
	
	//关闭GPS
	GPS_EN = OFF;	


	if(ERROR_CNT >= 10){
		//接收失败
		return;
	}

	//接收成功时
	//数据有效性检查
	//1,有效位
	//2,checksum
	
	//有效位检查
	if(*(GPS_BUFF_P-8) == 'V')
	{
		//无效数据直接返回
		return;
	}
	
	//checksum检查
	CHECK_SUM = 0;
	GPS_BUFF_P = GPS_BUFF;
	while(*GPS_BUFF_P != '*' )
	{
		CHECK_SUM ^= *GPS_BUFF_P;
		GPS_BUFF_P++;
	}
	
	if(CHECK_SUM != hex2dec(*(GPS_BUFF_P+1))*16 + hex2dec(*(GPS_BUFF_P+2)) )
	{
		//checksum检查失败直接返回
		return;
	}
	
	
	//数据写入FLASH条件
	//1,数据接收成功
	//2,有效位检查成功
	//3,checksum检查成功
	
	//!Todo 数据写入FLASH
	
	
	
	SLEEP_CNT = 0;	//数据收集成功时数据获取间隔清零
	
	//!Todo切换时钟
	// LFXT1 HF Mode -> VLOCK

	
	//重新启动计数
	TACTL|=BIT4;
	
	//回到睡眠模式
	return;
}



unsigned char hex2dec(unsigned char hex){
	
	if(hex < 58) return hex - 48;
	
	return hex - 87;
}






