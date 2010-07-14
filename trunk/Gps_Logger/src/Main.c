#include <msp430x14x.h>
#include "system.h"
#include "mmc.h"
#include "znfat.h"
#include "string.h"
//#include <stdio.h>

struct FAT32_Init_Arg Init_Arg_Mmc;	   //��ʼ�������ṹ��ʵ��
struct FileInfoStruct FileInfo; 	   //�ļ���Ϣ�ṹ��ʵ��
struct FAT32_Init_Arg *pArg=&Init_Arg_Mmc;
unsigned char Dev_No=0;
unsigned char Create_DT[6]={0x09,0x07,0x0d,0x0d,0x14,0x0f}; //����ʱ�� 09��07��0d��0dʱ14��0f��

unsigned long cardSize = 0;
unsigned char status = 1;
unsigned int timeout = 0;
int i = 0;







int main( void )
{
	WDTCTL = WDTPW + WDTHOLD;
	//Initialisation of the System Clock/GIO/Timer_A
	CLK_Init();
	TIMER_A_Init();
	P5DIR = 0xff;
	P5OUT = 0xff;

	//Initialisation of the GPS receiver

	//Initialisation of the MMC/SD-card
	while (status != 0)						// if return in not NULL an error did occur and the
										// MMC/SD-card will be initialized again 
{
status = initMMC();
timeout++;
if (timeout == 50)						// Try 50 times till error
{
//		printf ("No MMC/SD-card found!! %x\n", status);
  P5OUT=0xaa;
  break;
}
}

  while ((mmc_ping() != MMC_SUCCESS));		// Wait till card is inserted

  // Read the Card Size from the CSD Register
  cardSize =  MMC_ReadCardSize();
  
  FAT32_Init();
  FAT32_Create_File(&FileInfo,"\\�����ļ�.txt",Create_DT);
  FAT32_Add_Dat(&FileInfo,strlen("����һ������znFat��SD���ļ��������Գ���"),"����һ������znFat��SD���ļ��������Գ���");
	
  mmc_GoIdle(); 							// set MMC in Idle mode

  while (1);
}






void CLK_Init(void)
{
	unsigned char i;
	
LOOP:
	BCSCTL1&=~BIT7;		//���ⲿ8M����
	IFG1&=~BIT1;		//���OFIFG
	for(i=50;i>0;i--);
	{
		if(IFG1&BIT1)
		{
			goto LOOP;
		}
	}
//	BCSCTL2=0x8e;	//ѡ���ⲿ8M���񣬲���Ƶ��ΪMCLKʱ�ӣ����ⲿ8M����8��Ƶ��ΪSMCLKʱ��
	//ѡ���ⲿ8M���񣬲���Ƶ��ΪMCLK,SMCLKʱ��
	//ѡ���ⲿ32.768K����,8��Ƶ��ΪACLKʱ��
	BCSCTL2=0x88;	
}


unsigned char delay_flag=0;
void TIMER_A_Init(void)
{
	//ѡ��ACLK��Ϊʱ��Դ��8��Ƶ����32.768KkHZ/8/8 = 512Hz��,������ģʽ,ֹͣ����
	TACTL=0x0200;
	TACCTL0=CCIE;
	_BIS_SR(GIE);
}

//TIMER_A�жϷ������
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	TACTL&=~BIT4;	//ֹͣ����
	delay_flag=1;
}

void delay_x_us(unsigned int t)   //��ȷ��ʱt΢��
{
	TACTL|=BIT4;  //������ģʽ
	TACCR0=t;
	while(!delay_flag);
	delay_flag=0;
}

void delay_x_ms(unsigned int t)   //��ȷ��ʱt΢��
{
	unsigned int i;
	for(i=t;i;i--)
	{
		delay_x_us(1000);
	}
}






