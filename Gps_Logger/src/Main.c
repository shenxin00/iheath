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
  FAT32_Create_File(&FileInfo,"\\测试文件.txt",Create_DT);
  FAT32_Add_Dat(&FileInfo,strlen("这是一个基于znFat的SD卡文件操作测试程序！"),"这是一个基于znFat的SD卡文件操作测试程序！");
	
  mmc_GoIdle(); 							// set MMC in Idle mode

  while (1);
}






void CLK_Init(void)
{
	unsigned char i;
	
LOOP:
	BCSCTL1&=~BIT7;		//打开外部8M晶振
	IFG1&=~BIT1;		//清除OFIFG
	for(i=50;i>0;i--);
	{
		if(IFG1&BIT1)
		{
			goto LOOP;
		}
	}
//	BCSCTL2=0x8e;	//选择外部8M晶振，不分频作为MCLK时钟，对外部8M晶振8分频作为SMCLK时钟
	//选择外部8M晶振，不分频作为MCLK,SMCLK时钟
	//选择外部32.768K晶振,8分频作为ACLK时钟
	BCSCTL2=0x88;	
}


unsigned char delay_flag=0;
void TIMER_A_Init(void)
{
	//选择ACLK作为时钟源，8分频（即32.768KkHZ/8/8 = 512Hz）,增计数模式,停止计数
	TACTL=0x0200;
	TACCTL0=CCIE;
	_BIS_SR(GIE);
}

//TIMER_A中断服务程序
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	TACTL&=~BIT4;	//停止计数
	delay_flag=1;
}

void delay_x_us(unsigned int t)   //精确延时t微妙
{
	TACTL|=BIT4;  //增计数模式
	TACCR0=t;
	while(!delay_flag);
	delay_flag=0;
}

void delay_x_ms(unsigned int t)   //精确延时t微妙
{
	unsigned int i;
	for(i=t;i;i--)
	{
		delay_x_us(1000);
	}
}






