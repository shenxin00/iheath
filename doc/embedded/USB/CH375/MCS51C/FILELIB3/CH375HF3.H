/* 2004.06.05, 2004.09.20, 2004.10.22, 2004.11.20, 2004.12.12, 2004.12.28, 2005.01.04, 2005.01.12, 2005.01.26, 2005.03.01, 2005.07.29, 2005.12.28, 2006.08.02
****************************************
**  Copyright  (C)  W.ch  1999-2005   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH375 **
**  TC2.0@PC, KC7.0@MCS51             **
****************************************
*/
/* CH375 �����ļ�ϵͳ�ӿ� V3.0 */
/* ֧��: FAT12/FAT16/FAT32ֻ�� */
/* MCS51��Ƭ��, ��ѯ��ʽ�����жϷ�ʽ, ֧��С/��/��ģʽ���� */
/* ֧��3�����ݴ�ȡ��ʽ: ��ͨ�ĵ�DPTR�л���ʽ, ATMEL/PHILIPS/SST�ȵ�Ƭ����˫DPTR�л���ʽ, ��P2+R0ָ��˿ڶ���DPTRָ���ⲿRAM�ķ�ʽ */

#ifndef __CH375HF_H__
#define __CH375HF_H__

#define CH375_LIB_VER		0x30

#ifdef __cplusplus
extern "C" {
#endif

/* FILE: CH375INC.H */

/* ********************************************************************************************************************* */
/* Ӳ������ */

#define	CH375_MAX_DATA_LEN	0x40			/* ������ݰ��ĳ���, �ڲ��������ĳ��� */

/* ********************************************************************************************************************* */
/* ������� */

#define	CMD_RESET_ALL		0x05			/* ִ��Ӳ����λ */

#define	CMD_CHECK_EXIST		0x06			/* ���Թ���״̬ */
/* ����: �������� */
/* ���: �������ݵİ�λȡ�� */

#define	CMD_SET_USB_ID		0x12			/* �豸��ʽ: ����USB����VID�Ͳ�ƷPID */
/* ����: ����ID���ֽ�, ����ID���ֽ�, ��ƷID���ֽ�, ��ƷID���ֽ� */

#define	CMD_SET_USB_ADDR	0x13			/* ����USB��ַ */
/* ����: ��ֵַ */

#define	CMD_SET_USB_MODE	0x15			/* ����USB����ģʽ */
/* ����: ģʽ���� */
/*       00H=δ���õ��豸��ʽ, 01H=�����õ��豸��ʽ����ʹ���ⲿ�̼�ģʽ, 02H=�����õ��豸��ʽ����ʹ�����ù̼�ģʽ, 03H=�����õ��豸��ʽ����ʹ���ж϶˵�����ù̼�ģʽ */
/*       04H=δ���õ�������ʽ, 05H=�����õ�������ʽ, 06H=�����õ�������ʽ�����Զ�����SOF��, 07H=�����õ�������ʽ���Ҹ�λUSB���� */
/* ���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) */

#define	CMD_SET_ENDP2		0x18			/* �豸��ʽ: ����USB�˵�0�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD_SET_ENDP3		0x19			/* �豸��ʽ: ����USB�˵�0�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD_SET_ENDP4		0x1A			/* �豸��ʽ: ����USB�˵�1�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD_SET_ENDP5		0x1B			/* �豸��ʽ: ����USB�˵�1�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD_SET_ENDP6		0x1C			/* ����USB�˵�2/�����˵�Ľ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-������������ACK, 1110-��æNAK, 1111-����STALL */

#define	CMD_SET_ENDP7		0x1D			/* ����USB�˵�2/�����˵�ķ����� */
/* ����: ������ʽ */
/*           λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
/*           λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-����������Ӧ��, 1110-��æNAK, 1111-����STALL */

#define	CMD_GET_TOGGLE		0x0A			/* ��ȡOUT�����ͬ��״̬ */
/* ����: ����1AH */
/* ���: ͬ��״̬ */
/*           λ4Ϊ1��OUT����ͬ��, ����OUT����ͬ�� */

#define	CMD_GET_STATUS		0x22			/* ��ȡ�ж�״̬��ȡ���ж����� */
/* ���: �ж�״̬ */

#define	CMD_UNLOCK_USB		0x23			/* �豸��ʽ: �ͷŵ�ǰUSB������ */

#define	CMD_RD_USB_DATA		0x28			/* �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�, ���ͷŻ����� */
/* ���: ����, ������ */

#define	CMD_WR_USB_DATA3	0x29			/* �豸��ʽ: ��USB�˵�0�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

#define	CMD_WR_USB_DATA5	0x2A			/* �豸��ʽ: ��USB�˵�1�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

#define	CMD_WR_USB_DATA7	0x2B			/* ��USB�˵�2�ķ��ͻ�����д�����ݿ� */
/* ����: ����, ������ */

/* ************************************************************************** */
/* ������������USB������ʽ, ֻ��CH375֧�� */

#define	CMD_SET_BAUDRATE	0x02			/* ���ڷ�ʽ: ���ô���ͨѶ������ */
/* ����: �����ʷ�Ƶϵ��, �����ʷ�Ƶ���� */
/* ���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) */

#define	CMD_ABORT_NAK		0x17			/* ������ʽ: ������ǰNAK������ */

#define	CMD_SET_RETRY		0x0B			/* ������ʽ: ����USB������������Դ��� */
/* ����: ����25H, ���Դ��� */
/*                    λ7Ϊ1���յ�NAKʱ��������, λ3~λ0Ϊ��ʱ������Դ��� */

#define	CMD_ISSUE_TOKEN		0x4F			/* ������ʽ: ��������, ִ������ */
/* ����: �������� */
/*           ��4λ������, ��4λ�Ƕ˵�� */
/* ����ж� */

#define	CMD_CLR_STALL		0x41			/* ������ʽ: ���ƴ���-����˵���� */
/* ����: �˵�� */
/* ����ж� */

#define	CMD_SET_ADDRESS		0x45			/* ������ʽ: ���ƴ���-����USB��ַ */
/* ����: ��ֵַ */
/* ����ж� */

#define	CMD_GET_DESCR		0x46			/* ������ʽ: ���ƴ���-��ȡ������ */
/* ����: ���������� */
/* ����ж� */

#define	CMD_SET_CONFIG		0x49			/* ������ʽ: ���ƴ���-����USB���� */
/* ����: ����ֵ */
/* ����ж� */

#define	CMD_DISK_INIT		0x51			/* ������ʽ: ��ʼ��USB�洢�� */
/* ����ж� */

#define	CMD_DISK_RESET		0x52			/* ������ʽ: ��λUSB�洢�� */
/* ����ж� */

#define	CMD_DISK_SIZE		0x53			/* ������ʽ: ��ȡUSB�洢�������� */
/* ����ж� */

#define	CMD_DISK_READ		0x54			/* ������ʽ: ��USB�洢�������ݿ�(������512�ֽ�Ϊ��λ) */
/* ����: LBA������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
/* ����ж� */

#define	CMD_DISK_RD_GO		0x55			/* ������ʽ: ����ִ��USB�洢���Ķ����� */
/* ����ж� */

#define	CMD_DISK_WRITE		0x56			/* ������ʽ: ��USB�洢��д���ݿ�(������512�ֽ�Ϊ��λ) */
/* ����: LBA������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
/* ����ж� */

#define	CMD_DISK_WR_GO		0x57			/* ������ʽ: ����ִ��USB�洢����д���� */
/* ����ж� */

/* ************************************************************************** */
/* ����������V2.0������, ��CH372A/CH375A֧�� */

#define	CMD_GET_IC_VER		0x01			/* ��ȡоƬ���̼��汾 */
/* ���: �汾��( λ7Ϊ1, λ6Ϊ0, λ5~λ0Ϊ�汾�� ) */
/*           CH375������ЧֵΪ5FH, CH375A���ذ汾�ŵ�ֵΪ0A2H */

#define	CMD_ENTER_SLEEP		0x03			/* ����˯��״̬ */

#define	CMD_RD_USB_DATA0	0x27			/* �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ� */
/* ���: ����, ������ */

#define	CMD_DELAY_100US		0x0F			/* ���ڷ�ʽ: ��ʱ100uS */
/* ���: ��ʱ�ڼ����0, ��ʱ���������0 */

#define	CMD_CHK_SUSPEND		0x0B			/* �豸��ʽ: ���ü��USB���߹���״̬�ķ�ʽ */
/* ����: ����10H, ��鷽ʽ */
/*                    00H=�����USB����, 04H=��50mSΪ������USB����, 05H=��10mSΪ������USB���� */

#define	CMD_SET_SYS_FREQ	0x04			/* ����ϵͳ����Ƶ�� */
/* ����: Ƶ�� */
/*           00H=12MHz, 01H=1.5MHz */

/* ************************************************************************** */
/* ���¸Ľ���V2.0������, ����USB������ʽ, ��CH375A֧�� */

/*#define	CMD_SET_RETRY		0x0B*/			/* ������ʽ: ����USB������������Դ��� */
/* ����: ����25H, ���Դ��� */
/*                    λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������, λ7Ϊ1λ6Ϊ1���յ�NAKʱ����200mS, λ5~λ0Ϊ��ʱ������Դ��� */

/* ************************************************************************** */
/* ����������V2.0������, ����USB������ʽ, ��CH375A֧�� */

#define	CMD_TEST_CONNECT	0x16			/* ������ʽ: ���USB�豸����״̬ */
/* ���: ״̬( USB_INT_CONNECT��USB_INT_DISCONNECT, ����ֵ˵������δ��� ) */

#define	CMD_AUTO_SETUP		0x4D			/* ������ʽ: �Զ�����USB�豸 */
/* ����ж� */

#define	CMD_ISSUE_TKN_X		0x4E			/* ������ʽ: ����ͬ������, ִ������ */
/* ����: ͬ����־, �������� */
/*           ͬ����־��λ7Ϊ�����˵�IN��ͬ������λ, λ6Ϊ�����˵�OUT��ͬ������λ, λ5~λ0����Ϊ0 */
/*           �������Եĵ�4λ������, ��4λ�Ƕ˵�� */
/* ����ж� */

#define	CMD_SET_DISK_LUN	0x0B			/* ������ʽ: ����USB�洢���ĵ�ǰ�߼���Ԫ�� */
/* ����: ����34H, �µĵ�ǰ�߼���Ԫ��(00H-0FH) */

#define	CMD_DISK_BOC_CMD	0x50			/* ������ʽ: ��USB�洢��ִ��BulkOnly����Э������� */
/* ����ж� */

#define	CMD_DISK_INQUIRY	0x58			/* ������ʽ: ��ѯUSB�洢������ */
/* ����ж� */

#define	CMD_DISK_READY		0x59			/* ������ʽ: ���USB�洢������ */
/* ����ж� */

#define	CMD_DISK_R_SENSE	0x5A			/* ������ʽ: ���USB�洢������ */
/* ����ж� */

#define	CMD_DISK_MAX_LUN	0x5D			/* ������ʽ: ��ȡUSB�洢������߼���Ԫ�� */
/* ����ж� */

/* ********************************************************************************************************************* */
/* ����״̬ */

#define	CMD_RET_SUCCESS		0x51			/* ��������ɹ� */
#define	CMD_RET_ABORT		0x5F			/* �������ʧ�� */

/* ********************************************************************************************************************* */
/* USB�ж�״̬ */

/* ����״̬����Ϊ�����¼��ж�, ��CH372A/CH375A֧��, ���ͨ��CMD_CHK_SUSPEND����USB���߹�����, ��ô���봦��USB���߹����˯�߻��ѵ��ж�״̬ */
#define	USB_INT_USB_SUSPEND	0x05			/* USB���߹����¼� */
#define	USB_INT_WAKE_UP		0x06			/* ��˯���б������¼� */

/* ����״̬����0XH����USB�豸��ʽ */
/*   ���ù̼�ģʽ��ֻ��Ҫ����: USB_INT_EP1_IN, USB_INT_EP2_OUT, USB_INT_EP2_IN, ����CH372A/CH375A����Ҫ����: USB_INT_EP1_OUT */
/*   λ7-λ4Ϊ0000 */
/*   λ3-λ2ָʾ��ǰ����, 00=OUT, 10=IN, 11=SETUP */
/*   λ1-λ0ָʾ��ǰ�˵�, 00=�˵�0, 01=�˵�1, 10=�˵�2, 11=USB���߸�λ */
#define	USB_INT_EP0_SETUP	0x0C			/* USB�˵�0��SETUP */
#define	USB_INT_EP0_OUT		0x00			/* USB�˵�0��OUT */
#define	USB_INT_EP0_IN		0x08			/* USB�˵�0��IN */
#define	USB_INT_EP1_OUT		0x01			/* USB�˵�1��OUT */
#define	USB_INT_EP1_IN		0x09			/* USB�˵�1��IN */
#define	USB_INT_EP2_OUT		0x02			/* USB�˵�2��OUT */
#define	USB_INT_EP2_IN		0x0A			/* USB�˵�2��IN */
/* USB_INT_BUS_RESET	0x0000XX11B */		/* USB���߸�λ */
#define	USB_INT_BUS_RESET1	0x03			/* USB���߸�λ */
#define	USB_INT_BUS_RESET2	0x07			/* USB���߸�λ */
#define	USB_INT_BUS_RESET3	0x0B			/* USB���߸�λ */
#define	USB_INT_BUS_RESET4	0x0F			/* USB���߸�λ */

/* ����״̬����2XH-3XH����USB������ʽ��ͨѶʧ�ܴ���, ��CH375/CH375A֧�� */
/*   λ7-λ6Ϊ00 */
/*   λ5Ϊ1 */
/*   λ4ָʾ��ǰ���յ����ݰ��Ƿ�ͬ�� */
/*   λ3-λ0ָʾ����ͨѶʧ��ʱUSB�豸��Ӧ��: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=��ʱ */
/* USB_INT_RET_ACK	0x001X0010B */			/* ����:����IN���񷵻�ACK */
/* USB_INT_RET_NAK	0x001X1010B */			/* ����:����NAK */
/* USB_INT_RET_STALL	0x001X1110B */		/* ����:����STALL */
/* USB_INT_RET_DATA0	0x001X0011B */		/* ����:����OUT/SETUP���񷵻�DATA0 */
/* USB_INT_RET_DATA1	0x001X1011B */		/* ����:����OUT/SETUP���񷵻�DATA1 */
/* USB_INT_RET_TOUT	0x001XXX00B */			/* ����:���س�ʱ */
/* USB_INT_RET_TOGX	0x0010X011B */			/* ����:����IN���񷵻����ݲ�ͬ�� */
/* USB_INT_RET_PID	0x001XXXXXB */			/* ����:δ���� */

/* ����״̬����1XH����USB������ʽ�Ĳ���״̬����, ��CH375/CH375A֧�� */

#define	USB_INT_SUCCESS		0x14			/* USB������ߴ�������ɹ� */
#define	USB_INT_CONNECT		0x15			/* ��⵽USB�豸�����¼� */
#define	USB_INT_DISCONNECT	0x16			/* ��⵽USB�豸�Ͽ��¼� */
#define	USB_INT_BUF_OVER	0x17			/* USB���ƴ��������̫��, ��������� */
#define	USB_INT_DISK_READ	0x1D			/* USB�洢�������ݿ�, �������ݶ��� */
#define	USB_INT_DISK_WRITE	0x1E			/* USB�洢��д���ݿ�, ��������д�� */
#define	USB_INT_DISK_ERR	0x1F			/* USB�洢������ʧ�� */

/* ********************************************************************************************************************* */
/* ����USB���� */

/* USB�İ���ʶPID, ������ʽ�����õ� */
#define	DEF_USB_PID_NULL	0x00			/* ����PID, δ���� */
#define	DEF_USB_PID_SOF		0x05
#define	DEF_USB_PID_SETUP	0x0D
#define	DEF_USB_PID_IN		0x09
#define	DEF_USB_PID_OUT		0x01
#define	DEF_USB_PID_ACK		0x02
#define	DEF_USB_PID_NAK		0x0A
#define	DEF_USB_PID_STALL	0x0E
#define	DEF_USB_PID_DATA0	0x03
#define	DEF_USB_PID_DATA1	0x0B
#define	DEF_USB_PID_PRE		0x0C

/* USB��������, ���ù̼�ģʽ�����õ� */
#define	DEF_USB_REQ_READ	0x80			/* ���ƶ����� */
#define	DEF_USB_REQ_WRITE	0x00			/* ����д���� */
#define	DEF_USB_REQ_TYPE	0x60			/* ������������ */
#define	DEF_USB_REQ_STAND	0x00			/* ��׼���� */
#define	DEF_USB_REQ_CLASS	0x20			/* �豸������ */
#define	DEF_USB_REQ_VENDOR	0x40			/* �������� */
#define	DEF_USB_REQ_RESERVE	0x60			/* �������� */

/* USB��׼�豸����, RequestType��λ6λ5=00(Standard), ���ù̼�ģʽ�����õ� */
#define	DEF_USB_CLR_FEATURE	0x01
#define	DEF_USB_SET_FEATURE	0x03
#define	DEF_USB_GET_STATUS	0x00
#define	DEF_USB_SET_ADDRESS	0x05
#define	DEF_USB_GET_DESCR	0x06
#define	DEF_USB_SET_DESCR	0x07
#define	DEF_USB_GET_CONFIG	0x08
#define	DEF_USB_SET_CONFIG	0x09
#define	DEF_USB_GET_INTERF	0x0A
#define	DEF_USB_SET_INTERF	0x0B
#define	DEF_USB_SYNC_FRAME	0x0C

/* ********************************************************************************************************************* */

/* FILE: CH375HF.H */

#ifdef __CX51__
#ifndef __C51__
#define __C51__		1
#endif
#endif

#ifdef __C51__
typedef bit bdata                    BOOL1;
#else
#define data
#define idata
#define xdata
typedef unsigned char                BOOL1;
#endif

#ifndef UINT8
typedef unsigned char                UINT8;
#endif
#ifndef UINT16
typedef unsigned short               UINT16;
#endif
#ifndef UINT32
typedef unsigned long                UINT32;
#endif
#ifndef UINT8D
typedef unsigned char  data          UINT8D;
#endif
#ifndef UINT16D
typedef unsigned short data          UINT16D;
#endif
#ifndef UINT32D
typedef unsigned long  data          UINT32D;
#endif
#ifndef UINT8I
typedef unsigned char  idata         UINT8I;
#endif
#ifndef UINT16I
typedef unsigned short idata         UINT16I;
#endif
#ifndef UINT32I
typedef unsigned long  idata         UINT32I;
#endif
#ifndef UINT8X
typedef unsigned char  xdata         UINT8X;
#endif
#ifndef UINT16X
typedef unsigned short xdata         UINT16X;
#endif
#ifndef UINT32X
typedef unsigned long  xdata         UINT32X;
#endif
#ifndef PUINT8
typedef unsigned char               *PUINT8;
#endif
#ifndef PUINT16
typedef unsigned short              *PUINT16;
#endif
#ifndef PUINT32
typedef unsigned long               *PUINT32;
#endif
#ifndef PUINT8I
typedef unsigned char  idata        *PUINT8I;
#endif
#ifndef PUINT16I
typedef unsigned short idata        *PUINT16I;
#endif
#ifndef PUINT32I
typedef unsigned long  idata        *PUINT32I;
#endif
#ifndef PUINT8X
typedef unsigned char  xdata        *PUINT8X;
#endif
#ifndef PUINT16X
typedef unsigned short xdata        *PUINT16X;
#endif
#ifndef PUINT32X
typedef unsigned long  xdata        *PUINT32X;
#endif
#ifndef PUINT8C
typedef unsigned char  code         *PUINT8C;
#endif
#ifndef UINT8V
typedef unsigned char volatile       UINT8V;
#endif
#ifndef UINT8DV
typedef unsigned char volatile data  UINT8DV;
#endif
#ifndef UINT8XV
typedef unsigned char volatile xdata UINT8XV;
#endif

/* ������ */
#define ERR_SUCCESS				0x00	/* �����ɹ� */
#define ERR_CH375_ERROR			0x81	/* CH375Ӳ������,������Ҫ��λCH375 */
#define ERR_DISK_DISCON			0x82	/* ������δ����,���ܴ����Ѿ��Ͽ� */
#define ERR_STATUS_ERR			0x83	/* ����״̬����,�����������ӻ��߶Ͽ����� */
#define ERR_MBR_ERROR			0x91	/* ���̵���������¼��Ч,���ܴ�����δ����������δ��ʽ�� */
#define ERR_TYPE_ERROR			0x92	/* ���̷������Ͳ�֧��,ֻ֧��FAT12/FAT16/BigDOS/FAT32,��Ҫ�ɴ��̹����������·��� */
#define ERR_BPB_ERROR			0xA1	/* ������δ��ʽ��,���߲�������,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
#define ERR_TOO_LARGE			0xA2	/* ���̷�������ʽ��������������4GB,������������250GB,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
#define ERR_FAT_ERROR			0xA3	/* ���̵��ļ�ϵͳ��֧��,ֻ֧��FAT12/FAT16/FAT32,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
#define ERR_DISK_FULL			0xB1	/* �����ļ�̫��,ʣ��ռ�̫�ٻ����Ѿ�û��,��Ҫ�������� */
#define ERR_FDT_OVER			0xB2	/* Ŀ¼���ļ�̫��,û�п��е�Ŀ¼��,FAT12/FAT16��Ŀ¼�µ��ļ���Ӧ������500��,��Ҫ�������� */
#define ERR_MISS_DIR			0xB3	/* ָ��·����ĳ����Ŀ¼û���ҵ�,������Ŀ¼���ƴ��� */
#define ERR_FILE_CLOSE			0xB4	/* �ļ��Ѿ��ر�,�����Ҫʹ��,Ӧ�����´��ļ� */
#define ERR_OPEN_DIR			0x41	/* ָ��·����Ŀ¼���� */
#define ERR_MISS_FILE			0x42	/* ָ��·�����ļ�û���ҵ�,�������ļ����ƴ��� */
#define ERR_FOUND_NAME			0x43	/* ��������ͨ�����ƥ����ļ���,�ļ�����������·�������������,�����Ҫʹ��,Ӧ�ô򿪸��ļ� */
/* ����2XH-3XH����USB������ʽ��ͨѶʧ�ܴ���,��CH375���� */
/* ����1XH����USB������ʽ�Ĳ���״̬����,��CH375���� */
#define	ERR_USB_CONNECT			0x15	/* ��⵽USB�豸�����¼�,�����Ѿ����� */
#define	ERR_USB_DISCON			0x16	/* ��⵽USB�豸�Ͽ��¼�,�����Ѿ��Ͽ� */
#define	ERR_USB_DISK_ERR		0x1F	/* USB�洢������ʧ��,�ڳ�ʼ��ʱ������USB�洢����֧��,�ڶ�д�����п����Ǵ����𻵻����Ѿ��Ͽ� */

/* ���̼��ļ�״̬ */
#define DISK_UNKNOWN			0x00	/* ��δ��ʼ��,δ֪״̬ */
#define DISK_DISCONNECT			0x01	/* ����û�����ӻ����Ѿ��Ͽ� */
#define DISK_CONNECT			0x02	/* �����Ѿ�����,������δ��ʼ�������޷�ʶ��ô��� */
#define DISK_MOUNTED			0x03	/* �����Ѿ���ʼ���ɹ�,������δ�����ļ�ϵͳ�����ļ�ϵͳ��֧�� */
#define DISK_READY				0x10	/* �Ѿ��������̵��ļ�ϵͳ�����ܹ�֧�� */
#define DISK_OPEN_ROOT			0x12	/* �Ѿ��򿪸�Ŀ¼,����ģʽ,ֻ��������Ϊ��λ��дĿ¼������,ʹ�ú����ر�,ע��FAT12/FAT16��Ŀ¼�ǹ̶����� */
#define DISK_OPEN_DIR			0x13	/* �Ѿ�����Ŀ¼,����ģʽ,ֻ��������Ϊ��λ��дĿ¼������ */
#define DISK_OPEN_FILE			0x14	/* �Ѿ����ļ�,����ģʽ,����������Ϊ��λ�������ݶ�д */
#define DISK_OPEN_FILE_B		0x15	/* �Ѿ����ļ�,�ֽ�ģʽ,�������ֽ�Ϊ��λ�������ݶ�д */

/* FAT���ͱ�־ */
#define DISK_FS_UNKNOWN			0		/* δ֪���ļ�ϵͳ */
#define DISK_FAT12				1		/* FAT12�ļ�ϵͳ */
#define DISK_FAT16				2		/* FAT16�ļ�ϵͳ */
#define DISK_FAT32				3		/* FAT32�ļ�ϵͳ */

/* �ļ����� */
#define ATTR_READ_ONLY			0x01	/* �ļ�Ϊֻ������ */
#define ATTR_HIDDEN				0x02	/* �ļ�Ϊ�������� */
#define ATTR_SYSTEM				0x04	/* �ļ�Ϊϵͳ���� */
#define ATTR_VOLUME_ID			0x08	/* ���� */
#define ATTR_DIRECTORY			0x10	/* ��Ŀ¼ */
#define ATTR_ARCHIVE			0x20	/* �ļ�Ϊ�浵���� */
#define ATTR_LONG_NAME			( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )
/* �ļ����� UINT8 */
/* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
/*  ֻ   ��   ϵ   ��   Ŀ   ��   δ����   */
/*  ��   ��   ͳ   ��   ¼   ��            */
/* �ļ�ʱ�� UINT16 */
/* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )	( (h<<11) + (m<<5) + (s>>1) )	/* ����ָ��ʱ������ļ�ʱ������ */
/* �ļ����� UINT16 */
/* Date = ((Year-1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	/* ����ָ�������յ��ļ��������� */

/* �ļ��� */
#define PATH_WILDCARD_CHAR		0x2A	/* ·������ͨ��� '*' */
#define PATH_SEPAR_CHAR1		0x5C	/* ·�����ķָ��� '\' */
#define PATH_SEPAR_CHAR2		0x2F	/* ·�����ķָ��� '/' */
#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN			30		/* ���·������,������б�ָܷ�����С���������Լ�·��������00H */
#endif
#ifndef MAX_BYTE_IO
#define MAX_BYTE_IO		( MAX_PATH_LEN - 1 )	/* ���ֽ�Ϊ��λ���ζ�д�ļ�ʱ����󳤶�,�����ó��ȿ��Էֶ�ζ�д */
#endif

/* �ⲿ������� */
typedef union _CMD_PARAM {
	struct {
		UINT8	mBuffer[ MAX_PATH_LEN ];
	} Other;
	struct {
		UINT32	mDiskSizeSec;			/* ����: �����������̵��������� */
		UINT32	mTotalSector;			/* ����: ��ǰ�߼��̵��������� */
		UINT32	mFreeSector;			/* ����: ��ǰ�߼��̵�ʣ�������� */
		UINT8	mDiskFat;				/* ����: ��ǰ�߼��̵�FAT���� */
	} Query;							/* CMD_DiskQuery, ��ѯ������Ϣ */
	struct {
		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
	} Open;								/* CMD_FileOpen, ���ļ� */
	struct {
		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��(��ͨ���*)...,ö�����], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILE*",00H */
	} Enumer;							/* CMD_FileEnumer, ö���ļ�,�����ļ��� */
	struct {
		UINT8	mUpdateLen;				/* �������: �Ƿ��������³���: 0��ֹ,1���� */
	} Close;							/* CMD_FileClose, �رյ�ǰ�ļ� */
	struct {
		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
	} Create;							/* CMD_FileCreate, �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
	struct {
		UINT8	mPathName[ MAX_PATH_LEN ];	/* �������: ·��: [�̷�,ð��,б��,Ŀ¼�������ļ�������չ��...,������00H], �����̷���ð�ſ���ʡ��, ����"C:\DIR1.EXT\DIR2\FILENAME.EXT",00H */
	} Erase;							/* CMD_FileErase, ɾ���ļ����ر� */
	struct {
		UINT32	mFileSize;				/* �������: �µ��ļ�����,Ϊ0FFFFFFFFH���޸�, ����: ԭ���� */
		UINT16	mFileDate;				/* �������: �µ��ļ�����,Ϊ0FFFFH���޸�, ����: ԭ���� */
		UINT16	mFileTime;				/* �������: �µ��ļ�ʱ��,Ϊ0FFFFH���޸�, ����: ԭʱ�� */
		UINT8	mFileAttr;				/* �������: �µ��ļ�����,Ϊ0FFH���޸�, ����: ԭ���� */
	} Modify;							/* CMD_FileQuery, ��ѯ��ǰ�ļ�����Ϣ; CMD_FileModify, ��ѯ�����޸ĵ�ǰ�ļ�����Ϣ */
	struct {
		UINT32	mSectorOffset;			/* �������: ����ƫ��,0���ƶ����ļ�ͷ,0FFFFFFFFH���ƶ����ļ�β, ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������, 0FFFFFFFFH���ѵ��ļ�β */
	} Locate;							/* CMD_FileLocate, �ƶ���ǰ�ļ�ָ�� */
	struct {
		UINT8	mSectorCount;			/* �������: ��ȡ������, ����: ʵ�ʶ�ȡ������ */
	} Read;								/* CMD_FileRead, �ӵ�ǰ�ļ���ȡ���� */
	struct {
		UINT8	mSectorCount;			/* �������: д��������, ����: ʵ��д�������� */
	} Write;							/* CMD_FileWrite, ��ǰ�ļ�д������ */
	struct {
		UINT8	mSectorCount;			/* �������: ��ȡ������, ����: ʵ�ʶ�ȡ������ */
		UINT8	mReserved[7];
		PUINT8X	mDataBuffer;			/* �������: ��������ʼ��ַ, ����: ��������ǰ��ַ */
	} ReadX;							/* CMD_FileReadX, �ӵ�ǰ�ļ���ȡ���ݵ�ָ�������� */
	struct {
		UINT8	mSectorCount;			/* �������: д��������, ����: ʵ��д�������� */
		UINT8	mReserved[7];
		PUINT8X	mDataBuffer;			/* �������: ��������ʼ��ַ, ����: ��������ǰ��ַ */
	} WriteX;							/* CMD_FileWriteX, ��ǰ�ļ�д��ָ�������������� */
	struct {
		UINT32	mDiskSizeSec;			/* ����: �����������̵��������� */
	} DiskSize;							/* CMD_DiskSize, ��ѯ�������� */
	struct {
		UINT32	mByteOffset;			/* �������: ���ֽ�Ϊ��λ��ƫ����, ���ֽ�Ϊ��λ���ļ�ָ��, ����: ��ǰ�ļ�ָ���Ӧ�ľ�������������, 0FFFFFFFFH���ѵ��ļ�β */
	} ByteLocate;						/* CMD_ByteLocate, ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
	struct {
		UINT8	mByteCount;				/* �������: ׼����ȡ���ֽ���,���ô���MAX_BYTE_IO, ����: ʵ�ʶ������ֽ��� */
		UINT8	mByteBuffer[ MAX_BYTE_IO ];	/* ����: ���������ݿ� */
	} ByteRead;							/* CMD_ByteRead, ���ֽ�Ϊ��λ�ӵ�ǰ�ļ���ȡ���ݿ� */
	struct {
		UINT8	mByteCount;				/* �������: ׼��д����ֽ���,���ô���MAX_BYTE_IO, ����: ʵ��д����ֽ��� */
		UINT8	mByteBuffer[ MAX_BYTE_IO ];	/* �������: ׼��д������ݿ� */
	} ByteWrite;						/* CMD_ByteWrite, ���ֽ�Ϊ��λ��ǰ�ļ�д�����ݿ� */
	struct {
		UINT8	mSaveVariable;			/* �������: Ϊ0��ָ�����,��0ֵ�򱸷�/������� */
		UINT8	mReserved[3];
		PUINT8X	mBuffer;				/* �������: ָ���ӳ����ı����ı��ݻ�����,���Ȳ�С��80���ֽ� */
	} SaveVariable;						/* CMD_SaveVariable, ����/����/�ָ��ӳ����ı��� */
	union {
		struct {
			UINT32	mCBW_Sig;
			UINT32	mCBW_Tag;
			UINT8	mCBW_DataLen;		/* ����: ���ݴ��䳤��,��Чֵ��0��255 */
			UINT8	mCBW_DataLen1;
			UINT8	mCBW_DataLen2;
			UINT8	mCBW_DataLen3;
			UINT8	mCBW_Flag;			/* ����: ���䷽��ȱ�־ */
			UINT8	mCBW_LUN;
			UINT8	mCBW_CB_Len;		/* ����: �����ĳ���,��Чֵ��1��16 */
			UINT8	mCBW_CB_Buf[6];		/* ����: �����,�û��������Ϊ16���ֽ� */
		} mCBW;							/* BulkOnlyЭ��������, ����CBW�ṹ */
		struct {
			UINT32	mCSW_Sig;
			UINT32	mCSW_Tag;
			UINT32	mCSW_Residue;		/* ����: ʣ�����ݳ��� */
			UINT8	mCSW_Status;		/* ����: ����ִ�н��״̬ */
			UINT8	mReserved;
		} mCSW;							/* BulkOnlyЭ�������״̬��, ���CSW�ṹ */
	} BOC;								/* CMD_BulkOnlyCmd, ִ�л���BulkOnlyЭ�������, ��������ݴ�����ô������DISK_BASE_BUF�� */
} CMD_PARAM;

typedef CMD_PARAM idata CMD_PARAM_I;
typedef CMD_PARAM data *P_CMD_PARAM;

/* FILE: CH375HF?.C */

//#define EN_DISK_WRITE			1
#define EN_DISK_FAT12			1
#define EN_DISK_FAT32			1
#define EN_BYTE_ACCESS			1
//#define EN_SAVE_VARIABLE		1
#define EXT_BLK_INTERFACE		1

#ifndef LIB_CFG_DISK_IO
#define LIB_CFG_DISK_IO			1		/* Ĭ�������,���̶�д�����ݵĸ��Ʒ�ʽΪ"��DPTR����" */
#endif
#ifndef LIB_CFG_FILE_IO
#define LIB_CFG_FILE_IO			1		/* Ĭ�������,�ļ���д�����ݵĸ��Ʒ�ʽΪ"��DPTR����" */
#endif
#ifndef LIB_CFG_UPD_SIZE
#define LIB_CFG_UPD_SIZE		0		/* Ĭ�������,���������ݺ��ļ����ȵĸ��·�ʽΪ"������" */
#endif
#ifndef LIB_CFG_NO_DLY
#define LIB_CFG_NO_DLY			0		/* Ĭ�������,��д�������������ʱ��ʽΪ"д����ʱ" */
#endif
#ifndef LIB_CFG_INT_EN
#define LIB_CFG_INT_EN			0		/* Ĭ�������,CH375��INT#�������ӷ�ʽΪ"��ѯ��ʽ" */
#endif

#define LIB_CFG_VALUE		( ( LIB_CFG_INT_EN << 7 ) | ( LIB_CFG_NO_DLY << 5 ) | ( LIB_CFG_UPD_SIZE << 4 ) | ( LIB_CFG_FILE_IO << 2 ) | LIB_CFG_DISK_IO )	/* CH375���������ֵ */

#ifndef DISK_BASE_BUF_ADDR
/*#define DISK_BASE_BUF_ADDR		0*/		/* ���δ������̶�д�Ļ�������ַ,��ô�ٶ����̶�д�Ļ������ӵ�ַ0��ʼ */
#endif

/* �ӳ�������ṩ�ı��� */
extern UINT8DV	CH375IntStatus;			/* CH375�������ж�״̬ */
extern UINT8DV	CH375DiskStatus;		/* ���̼��ļ�״̬ */
extern UINT8D	CH375LibConfig;			/* CH375���������,����˵�� */
/* λ7: CH375��INT#�������ӷ�ʽ: 0��ѯ��ʽ,1�жϷ�ʽ */
/* λ5: ��д�����������Ƿ���ʱ: 0д����ʱ,1����ʱ */
/* λ4: ���������ݺ��Ƿ��Զ������ļ�����: 0������,1�Զ����� */
/* λ3λ2: ����ļ���д�Ķ��������ݵĸ��Ʒ�ʽ: 00�ⲿ�ӳ���, 01��DPTR����, 10˫DPTR����, 11��DPTR��P2+R0���� */
/* λ1λ0: ��Դ��̶�д�ĵ��������ݵĸ��Ʒ�ʽ: 00��DPTR����, 01��DPTR����, 10˫DPTR����, 11��DPTR��P2+R0���� */

/* ���CH375��INT#�������ӵ���Ƭ�����ж��������Ų���׼��ʹ���жϷ�ʽ,��ôLIB_CFG_INT_EN����Ϊ1,������Ϊ0�ɵ�Ƭ����ѯINT#���� */
/* ����MCS51��Ƭ�������ⲿRAM�е�����ʱ�Ƚ���,����CH375�ĳ�����ṩ�����Ż��ٶȵķ�ʽ,��LIB_CFG_FILE_IO��LIB_CFG_DISK_IO�ж���:
   ��ʽ0:"�ⲿ�ӳ���", ֻ�������ļ���дʱ�����ݸ���(ֻ����CH375FileReadX��CH375FileWriteX�����ӳ���),LIB_CFG_DISK_IO��֧�ַ�ʽ0,
                       ��ָ���ӳ���xWriteToExtBuf��xReadFromExtBuf�������ݸ���,�������ӳ�������Ӧ�ó����ж����,��CH375�ĳ�������,
   ��ʽ1:"��DPTR����", �������ݸ��Ʒ�ʽ, ʹ��һ��DPTR�����л�, ÿ����һ���ֽ���Ҫ16����������, �ٶ�����, ����������MCS51��Ƭ��,
   ��ʽ2:"˫DPTR����", ����ض�Ӳ�������ݸ��Ʒ�ʽ, ʹ������DPTR, ÿ����һ���ֽ���Ҫ10����������, �ٶȽϿ�, ������ATMEL/PHILIPS/SST�Ⱦ���˫DPTR�ĵ�Ƭ��,
   ��ʽ3:"��DPTR��P2+R0����", ��P2+R0ָ��CH375��I/O�˿ڲ�����DPTRָ���ⲿRAM�������ݸ���, ÿ����һ���ֽ���Ҫ6.25����������, �ٶ����,
                       ���������б�׼��MCS51��Ƭ��, ����ĳЩ��Ƭ�����������õ��ⲿRAMʱ��ر�P2+R0�Ĺ���, ���Կ��ܲ�����,
   �����ļ����ݶ�д,Ҳ����Ӧ�ó������CH375FileReadX��CH375FileWriteX�ӳ���ʱ:
     �ڷ�ʽ0��,��Ӧ�ó�����xWriteToExtBuf��xReadFromExtBuf�ӳ��������й���������,�趨��������ֵ��,
     �ڷ�ʽ1,2,3��,Ӧ�ó���ÿ�ε���CH375FileReadX��CH375FileWriteXʱ,CH375�ĳ���ⶼ���ָ������������ʼ��ַ��ʼ��д����,
     ����: ĳ�ļ�����Ϊ1K(ռ��2������), �������CH375FileReadXʱ��1K(ָ��mCmdParam.Read.mSectorCountΪ2), ��ô1K����ȫ����ָ����������,
           �����������Сֻ��0.5K, ��ô�����ζ�ȡ, ��һ�ε���CH375FileReadXʱ��0.5K, ��������0.5K���ݺ��ٵ���CH375FileReadX����һ��0.5K������
*/
extern UINT8D	CH375vDiskFat;			/* �߼��̵�FAT��־:1=FAT12,2=FAT16,3=FAT32 */
extern UINT8D	CH375vSecPerClus;		/* �߼��̵�ÿ�������� */
extern UINT32D	CH375vStartCluster;		/* ��ǰ�ļ�����Ŀ¼����ʼ�غ� */
extern UINT32D	CH375vFileSize;			/* ��ǰ�ļ��ĳ��� */
extern UINT32D	CH375vCurrentOffset;	/* ��ǰ�ļ�ָ��,��ǰ��дλ�õ��ֽ�ƫ�� */

/* FAT���������ļ�Ŀ¼��Ϣ */
typedef struct _FAT_DIR_INFO {
	UINT8	DIR_Name[11];				/* 00H,�ļ���,��11�ֽ�,���㴦��ո� */
	UINT8	DIR_Attr;					/* 0BH,�ļ�����,�ο�ǰ���˵�� */
	UINT8	DIR_NTRes;					/* 0CH */
	UINT8	DIR_CrtTimeTenth;			/* 0DH,�ļ�������ʱ��,��0.1�뵥λ���� */
	UINT16	DIR_CrtTime;				/* 0EH,�ļ�������ʱ�� */
	UINT16	DIR_CrtDate;				/* 10H,�ļ����������� */
	UINT16	DIR_LstAccDate;				/* 12H,���һ�δ�ȡ���������� */
	UINT16	DIR_FstClusHI;				/* 14H */
	UINT16	DIR_WrtTime;				/* 16H,�ļ��޸�ʱ��,�ο�ǰ��ĺ�MAKE_FILE_TIME */
	UINT16	DIR_WrtDate;				/* 18H,�ļ��޸�����,�ο�ǰ��ĺ�MAKE_FILE_DATA */
	UINT16	DIR_FstClusLO;				/* 1AH */
	UINT32	DIR_FileSize;				/* 1CH,�ļ����� */
} FAT_DIR_INFO;							/* 20H */
typedef FAT_DIR_INFO xdata *P_FAT_DIR_INFO;

extern BOOL1	CH375Version2;			/* оƬ�汾:0-CH375,1-CH375A */
extern UINT32D	CH375vDataStart;		/* �߼��̵������������ʼLBA */
extern UINT32D	CH375vFdtLba;			/* ��ǰFDT���ڵ�LBA��ַ */
extern UINT16D	CH375vFdtOffset;		/* ��ǰFDT�������ڵ�ƫ�Ƶ�ַ */
extern UINT32X	CH375vDiskRoot;			/* ����FAT16��Ϊ��Ŀ¼ռ��������,����FAT32��Ϊ��Ŀ¼��ʼ�غ� */

extern UINT8	CH375ReadBlock( void );		/* �Ӵ��̶�ȡ������������ݵ��ⲿ�ӿڽ����� */
#ifdef EN_DISK_WRITE
extern UINT8	CH375WriteBlock( void );	/* ���ⲿ�ӿڽ������Ķ�����������ݿ�д����� */
#endif

/* �ӳ�������ṩ���ӳ��� */
/* �����ӳ�����, �ļ������ӳ���CH375File*�ʹ��̲�ѯ�ӳ���CH375DiskQuery�����ܻ��õ��������ݻ�����DISK_BASE_BUF,
   �����п�����DISK_BASE_BUF�б����˴�����Ϣ, ���Ա��뱣֤DISK_BASE_BUF��������������;,
   ���RAM����, Ҫ��DISK_BASE_BUF��ʱ����������;, ��ô����ʱ�����������CH375DirtyBuffer������̻����� */
extern UINT8	CH375GetVer( void );		/* ��ȡ��ǰ�ӳ����İ汾�� */
extern void		CH375Reset( void );			/* ��λCH375 */
extern UINT8	CH375Init( void );			/* ��ʼ��CH375 */
extern UINT8	CH375DiskConnect( void );	/* �������Ƿ����� */
extern UINT8	CH375DiskReady( void );		/* ��ѯ�����Ƿ�׼���� */
extern void		CH375DirtyBuffer( void );	/* ������̻����� */
extern UINT8	CH375FileOpen( void );		/* ���ļ�����ö���ļ� */
extern UINT8	CH375FileClose( void );		/* �رյ�ǰ�ļ� */
#ifdef EN_DISK_WRITE
extern UINT8	CH375FileErase( void );		/* ɾ���ļ����ر� */
extern UINT8	CH375FileCreate( void );	/* �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
#endif
extern UINT8	CH375FileModify( void );	/* ��ѯ�����޸ĵ�ǰ�ļ�����Ϣ */
extern UINT8	CH375FileLocate( void );	/* �ƶ���ǰ�ļ�ָ�� */
extern UINT8	CH375FileReadX( void );		/* �ӵ�ǰ�ļ���ȡ���ݵ�ָ�������� */
#ifdef EN_DISK_WRITE
extern UINT8	CH375FileWriteX( void );	/* ��ǰ�ļ�д��ָ�������������� */
#endif
#ifdef EN_BYTE_ACCESS
extern UINT8	CH375ByteLocate( void );	/* ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
extern UINT8	CH375ByteRead( void );		/* ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
#ifdef EN_DISK_WRITE
extern UINT8	CH375ByteWrite( void );		/* ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
#endif
#endif
extern UINT8	CH375DiskSize( void );		/* ��ѯ�������� */
extern UINT8	CH375DiskQuery( void );		/* ��ѯ������Ϣ */
#ifdef EN_SAVE_VARIABLE
extern void		CH375SaveVariable( void );	/* ����/����/�ָ��ӳ����ı���,�����ӳ�����ڶ��CH375оƬ֮������л� */
#endif
extern UINT8	CH375BulkOnlyCmd( void );	/* ִ�л���BulkOnlyЭ������� */
extern UINT8	CH375sDiskReady( void );	/* ��ѯ�����Ƿ�׼����,֧��CH375S */

/* ��ͷ�ļ�����ΪCH375�ӳ��������Ҫ��I/O���ڴ���Դ,��������Ҫ����Ӳ���йص�Ŀ�����,
   ������ļ��Ǳ�������Ŀ�Ķ��Դ���������Ϊͷ�ļ�,��ôӦ��ֻ����һ��ͷ�ļ�������Դ�Ͳ�������,
   ����֮���ͷ�ļ�Ӧ�ñ����ȶ���CH375HF_NO_CODE,�Ӷ���ֹ��ͷ�ļ������ظ���Ŀ�����,����:
#define		CH375HF_NO_CODE		1
#include	CH375HF?.H
*/
#ifdef CH375HF_NO_CODE

extern CMD_PARAM_I mCmdParam;				/* ������� */
extern UINT8XV CH375_CMD_PORT;				/* CH375����˿ڵ�I/O��ַ */
extern UINT8XV CH375_DAT_PORT;				/* CH375���ݶ˿ڵ�I/O��ַ */
extern UINT8X  DISK_BASE_BUF[512];			/* �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#ifdef FILE_DATA_BUF_LEN
extern UINT8X  FILE_DATA_BUF[ FILE_DATA_BUF_LEN ];	/* �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
extern UINT8	CH375FileRead( void );		/* �ӵ�ǰ�ļ���ȡ���� */
#ifdef EN_DISK_WRITE
extern UINT8	CH375FileWrite( void );		/* ��ǰ�ļ�д������ */
#endif
#endif
#ifndef NO_DEFAULT_CH375_F_ENUM
extern UINT8	CH375FileEnumer( void );	/* ö���ļ� */
#endif
#ifndef NO_DEFAULT_CH375_F_QUERY
extern UINT8	CH375FileQuery( void );		/* ��ѯ��ǰ�ļ�����Ϣ */
#endif
extern void xQueryInterrupt( void );		/* �ⲿ����ı�CH375�������õ��ӳ���,��ѯCH375�жϲ������ж�״̬ */
extern void xDelay100uS( void );			/* �ⲿ����ı�CH375�������õ��ӳ���,��ʱ100uS */
#ifdef EN_DISK_WRITE
extern void xDelayAfterWrite( void );		/* �ⲿ����ı�CH375�������õ��ӳ���,д��������ʱ */
#endif
extern void xFileNameEnumer( void );		/* �ⲿ����ı�CH375�������õ��ӳ���,�ļ���ö�ٻص��ӳ��� */
extern UINT8 CH375LibInit( void );			/* ��ʼ��CH375������CH375оƬ,�����ɹ�����0 */

#else

CMD_PARAM_I mCmdParam;					/* ������� */

UINT8XV CH375_CMD_PORT _at_ CH375_CMD_PORT_ADDR;	/* CH375����˿ڵ�I/O��ַ */
UINT8XV CH375_DAT_PORT _at_ CH375_DAT_PORT_ADDR;	/* CH375���ݶ˿ڵ�I/O��ַ */
#ifdef DISK_BASE_BUF_ADDR
UINT8X  DISK_BASE_BUF[512] _at_ DISK_BASE_BUF_ADDR;	/* �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#else
UINT8X  DISK_BASE_BUF[512];				/* �ⲿRAM�Ĵ������ݻ�����,����������Ϊһ�������ĳ��� */
#endif
#ifdef FILE_DATA_BUF_LEN
#ifdef FILE_DATA_BUF_ADDR
UINT8X  FILE_DATA_BUF[ FILE_DATA_BUF_LEN ] _at_ FILE_DATA_BUF_ADDR;	/* �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
#else
UINT8X  FILE_DATA_BUF[ FILE_DATA_BUF_LEN ];	/* �ⲿRAM���ļ����ݻ�����,���������Ȳ�С��һ�ζ�д�����ݳ��� */
#endif
UINT8	CH375FileRead( void )		/* �ӵ�ǰ�ļ���ȡ���� */
{
	mCmdParam.ReadX.mDataBuffer = &FILE_DATA_BUF[0];  /* ָ���ļ����ݻ����� */
	return( CH375FileReadX( ) );
}
#ifdef EN_DISK_WRITE
UINT8	CH375FileWrite( void )		/* ��ǰ�ļ�д������ */
{
	mCmdParam.WriteX.mDataBuffer = &FILE_DATA_BUF[0];  /* ָ���ļ����ݻ����� */
	return( CH375FileWriteX( ) );
}
#endif
#endif

/* ���³�����Ը�����Ҫ�޸� */

#ifndef NO_DEFAULT_CH375_F_ENUM			/* ��Ӧ�ó����ж���NO_DEFAULT_CH375_F_ENUM���Խ�ֹĬ�ϵ�ö���ļ�����,Ȼ�������б�д�ĳ�������� */
UINT8	CH375FileEnumer( void )			/* ö���ļ� */
{
	UINT8	status;
	status = CH375FileOpen( );
	if ( status == ERR_FOUND_NAME ) status = ERR_SUCCESS;  /* �����ɹ� */
	return( status );
}
#endif

#ifndef NO_DEFAULT_CH375_F_QUERY		/* ��Ӧ�ó����ж���NO_DEFAULT_CH375_F_QUERY���Խ�ֹĬ�ϵĲ�ѯ��ǰ�ļ�����Ϣ����,Ȼ�������б�д�ĳ�������� */
UINT8	CH375FileQuery( void )			/* ��ѯ��ǰ�ļ�����Ϣ */
{
	PUINT8I	buf;
	UINT8	count;
	buf = (PUINT8I)( & mCmdParam.Modify.mFileSize );
	for ( count = sizeof( mCmdParam.Modify ); count != 0; count -- ) {
		*buf = 0xFF;  /* �������ȫ����Ч,����ѯ���޸� */
		buf ++;
	}
	return( CH375FileModify( ) );
}
#endif

#ifndef NO_DEFAULT_CH375_INT			/* ��Ӧ�ó����ж���NO_DEFAULT_CH375_INT���Խ�ֹĬ�ϵ��жϴ�������,Ȼ�������б�д�ĳ�������� */
#if LIB_CFG_INT_EN == 0					/* CH375��INT#�������ӷ�ʽΪ"��ѯ��ʽ" */
void xQueryInterrupt( void )			/* ��ѯCH375�жϲ������ж�״̬ */
{
	while ( CH375_INT_WIRE );  /* ���CH375���ж���������ߵ�ƽ��ȴ� */
	CH375_CMD_PORT = CMD_GET_STATUS;  /* ��ȡ��ǰ�ж�״̬ */
	CH375IntStatus &= 0x80; if ( CH375IntStatus ) CH375IntStatus = 0;  /* ����������,����������ʱ2uS */
	CH375IntStatus = CH375_DAT_PORT;  /* ��ȡ�ж�״̬ */
	if ( CH375IntStatus == USB_INT_DISCONNECT ) CH375DiskStatus = DISK_DISCONNECT;  /* ��⵽USB�豸�Ͽ��¼� */
	else if ( CH375IntStatus == USB_INT_CONNECT ) CH375DiskStatus = DISK_CONNECT;  /* ��⵽USB�豸�����¼� */
}
#else									/* LIB_CFG_INT_EN != 0, CH375��INT#�������ӷ�ʽΪ"�жϷ�ʽ" */
void xQueryInterrupt( void )			/* ��ѯ�ж�״̬,�ȴ�Ӳ���ж� */
{
	while ( CH375IntStatus == 0 );		/* �ӳ������ø��ӳ���֮ǰCH375IntStatus=0,Ӳ���жϺ�,���жϷ��������Ϊ��0��ʵ���ж�״̬�󷵻� */
}
void	CH375Interrupt( void ) interrupt CH375_INT_NO using 1	/* CH375�жϷ������,ʹ�üĴ�����1,��CH375��INT#�ĵ͵�ƽ�����½��ش�����Ƭ���ж� */
{
	CH375_CMD_PORT = CMD_GET_STATUS;  /* ��ȡ�ж�״̬��ȡ���ж����� */
	CH375IntStatus &= 0x80; if ( CH375IntStatus ) CH375IntStatus = 0;  /* ����������,����������ʱ2uS */
	CH375IntStatus = CH375_DAT_PORT;  /* ��ȡ�ж�״̬ */
	if ( CH375IntStatus == USB_INT_DISCONNECT ) CH375DiskStatus = DISK_DISCONNECT;  /* ��⵽USB�豸�Ͽ��¼� */
	else if ( CH375IntStatus == USB_INT_CONNECT ) CH375DiskStatus = DISK_CONNECT;  /* ��⵽USB�豸�����¼� */
#ifdef CLEAR_INT_MARK
	CLEAR_INT_MARK( );  /* ĳЩ��Ƭ����Ҫ����������жϱ�־ */
#endif
}
#endif
#endif

#ifndef NO_DEFAULT_DELAY_100US			/* ��Ӧ�ó����ж���NO_DEFAULT_DELAY_100US���Խ�ֹĬ�ϵ���ʱ100uS�ӳ���,Ȼ�������б�д�ĳ�������� */
void xDelay100uS( void )				/* ��ʱ100uS */
{
	UINT8	count;
	for ( count = 150; count != 0; count -- );  /* ��ʱ100uS,2x333nS@36MHz&12T */
}
#endif

#ifdef EN_DISK_WRITE
#ifndef NO_DEFAULT_DELAY_WRITE			/* ��Ӧ�ó����ж���NO_DEFAULT_DELAY_WRITE���Խ�ֹĬ�ϵ�д��������ʱ����,Ȼ�������б�д�ĳ�������� */
void xDelayAfterWrite( void )			/* д��������ʱ */
{
	UINT8	count;
	for ( count = 250; count != 0; count -- );  /* ��ʱ200uS���� */
}
#endif
#endif

#ifndef NO_DEFAULT_FILE_ENUMER			/* ��Ӧ�ó����ж���NO_DEFAULT_FILE_ENUMER���Խ�ֹĬ�ϵ��ļ���ö�ٻص�����,Ȼ�������б�д�ĳ�������� */
void xFileNameEnumer( void )			/* �ļ���ö�ٻص��ӳ��� */
{
/* ���ָ��ö�����CH375vFileSizeΪ0xFFFFFFFF�����FileOpen����ôÿ������һ���ļ�FileOpen������ñ��ص�����
   �ص�����xFileNameEnumer���غ�FileOpen�ݼ�CH375vFileSize������ö��ֱ�����������ļ�����Ŀ¼�����������ǣ�
   �ڵ���FileOpen֮ǰ����һ��ȫ�ֱ���Ϊ0����FileOpen�ص�������󣬱�������CH375vFdtOffset�õ��ṹFAT_DIR_INFO��
   �����ṹ�е�DIR_Attr�Լ�DIR_Name�ж��Ƿ�Ϊ�����ļ�������Ŀ¼������¼�����Ϣ������ȫ�ֱ�������������
   ��FileOpen���غ��жϷ���ֵ�����ERR_MISS_FILE��ERR_FOUND_NAME����Ϊ�����ɹ���ȫ�ֱ���Ϊ����������Ч�ļ�����
   ����ڱ��ص�����xFileNameEnumer�н�CH375vFileSize��Ϊ1����ô����֪ͨFileOpen��ǰ���������������ǻص��������� */
#if 0
#ifdef FILE_DATA_BUF_LEN
	UINT8			i;
	UINT16			FileCount;
	P_FAT_DIR_INFO	pFileDir;
	PUINT8X			NameBuf;
	pFileDir = (P_FAT_DIR_INFO)( (PUINT8X)(&DISK_BASE_BUF[0]) + CH375vFdtOffset );  /* ��ǰFDT����ʼ��ַ */
	FileCount = (UINT16)( 0xFFFFFFFF - CH375vFileSize );  /* ��ǰ�ļ�����ö�����,CH375vFileSize��ֵ��0xFFFFFFFF,�ҵ��ļ�����ݼ� */
	if ( FileCount < FILE_DATA_BUF_LEN / 12 ) {  /* ��黺�����Ƿ��㹻���,�ٶ�ÿ���ļ�����ռ��12���ֽڴ�� */
		NameBuf = & FILE_DATA_BUF[ FileCount * 12 ];  /* ���㱣�浱ǰ�ļ����Ļ�������ַ */
		for ( i = 0; i < 11; i ++ ) NameBuf[ i ] = pFileDir -> DIR_Name[ i ];  /* �����ļ���,����Ϊ11���ַ�,δ�����ո� */
		if ( pFileDir -> DIR_Attr & ATTR_DIRECTORY ) NameBuf[ i ] = 1;  /* �ж���Ŀ¼�� */
		NameBuf[ i ] = 0;  /* �ļ��������� */
	}
#endif
#endif
}
#endif

#ifdef EXT_BLK_INTERFACE
#if LIB_CFG_FILE_IO == 0				/* �ļ���д�����ݵĸ��Ʒ�ʽΪ"�ⲿ�ӳ���" */
#ifdef LIB_CFG_FILE_IO_DEFAULT			/* ���Ӧ�ó����ж����ֵ��ʹ��Ĭ��"�ⲿ�ӳ���",����Ӧ�����б�д������� */
unsigned char xdata *current_buffer;	/* �����ļ����ݶ�дʱ�Ļ������ĵ�ǰָ��,��Ӧ�ó����ڵ���CH375FileReadX��CH375FileWriteX�ӳ���ǰ���ó�ֵ */
void xWriteToExtBuf( UINT8 mLength )	/* ���ӳ�����CH375���ӳ�������,���ڴ�CH375��ȡ�ļ����ݵ��ⲿ������,��CH375FileReadX���� */
{
/*	if ( (UINT16)current_buffer + mLength >= (UINT16)&FILE_DATA_BUF + sizeof( FILE_DATA_BUF ) ) return;*/  /* ��ֹ��������� */
	if ( mLength ) {
		do {  /* ���ݳ��ȶ�ȡ����,ʵ���ϳ�������CH375_MAX_DATA_LEN,Ҳ����64 */
			*current_buffer = CH375_DAT_PORT;  /* �������ݲ�����,���������ַ�ʽ���ļ����ݱ��浽��Ƭ���ĸ��ִ��д洢���� */
			current_buffer ++;
		} while ( -- mLength );
	}  /* �����������ݵ���ʱ�䲻�ó���2mS */
	else {  /* ����,�ָ���������ַ,������ļ����ݶ�д�Ļ������ĵ�ǰָ�����mCmdParam.ReadX.mDataBuffer����ᱻ�Զ��ָ�,������������г��� */
		current_buffer += (UINT16)mCmdParam.ReadX.mDataBuffer;  /* mDataBuffer��Ϊ��ֵ */
		mCmdParam.ReadX.mDataBuffer = 0;  /* Ϊ��֧������,�ڵ���CH375FileReadX֮ǰҲӦ����0 */
	}
}
#ifdef EN_DISK_WRITE
void xReadFromExtBuf( UINT8 mLength )	/* ���ӳ�����CH375���ӳ�������,���ڴ��ⲿ��������ȡ�ļ����ݵ�CH375,��CH375FileWriteX���� */
{
	if ( mLength ) {
		do {  /* ���ݳ���д������,ʵ���ϳ�������CH375_MAX_DATA_LEN,Ҳ����64 */
			CH375_DAT_PORT = *current_buffer;  /* ������д��,���������ַ�ʽ�ӵ�Ƭ���ĸ��ִ��д洢����ȡ���ļ����� */
			current_buffer ++;
		} while ( -- mLength );
	}  /* �����������ݵ���ʱ�䲻�ó���2mS */
	else {  /* ����,�ָ���������ַ,������ļ����ݶ�д�Ļ������ĵ�ǰָ�����mCmdParam.WriteX.mDataBuffer����ᱻ�Զ��ָ�,������������г��� */
		current_buffer += (UINT16)mCmdParam.WriteX.mDataBuffer;  /* mDataBuffer��Ϊ��ֵ */
		mCmdParam.WriteX.mDataBuffer = 0;  /* Ϊ��֧������,�ڵ���CH375FileWriteX֮ǰҲӦ����0 */
	}
}
#endif
#endif
#else									/* LIB_CFG_FILE_IO != 0,�ļ���д�����ݵĸ��Ʒ�ʽ����"�ⲿ�ӳ���" */
#ifdef FILE_DATA_BUF_LEN
void xWriteToExtBuf( UINT8 mLength )	/* ������ø��ӳ��� */
{
	mLength --;  /* �ò���������,ֻ�Ǳ�����־�����Ϣ */
}
#ifdef EN_DISK_WRITE
void xReadFromExtBuf( UINT8 mLength )	/* ������ø��ӳ��� */
{
	mLength --;  /* �ò���������,ֻ�Ǳ�����־�����Ϣ */
}
#endif
#endif
#endif
#endif

UINT8	CH375LibInit( void )  /* ��ʼ��CH375������CH375оƬ,�����ɹ�����0 */
{
	if ( SP > 0xF0 ) return( 0xFC );  /* ��Ƭ���Ķ�ջ�ռ䲻��,CH375�ӳ������������7���ӳ���,��ѯ��ʽ�����Ҫ14�ֽڵĶ�ջ�ռ�,�����ṩ���� */
	CH375LibConfig = LIB_CFG_VALUE;  /* CH375���������ֵ */
	DISK_BASE_BUF[0] = 0;  /* �ò���������,ֻ��Ϊ�˷�ֹ�������Ż�ʱ������DISK_BASE_BUF������ */
	if ( CH375GetVer( ) < CH375_LIB_VER ) return( 0xFF );  /* ��ȡ��ǰ�ӳ����İ汾��,�汾̫���򷵻ش��� */
	return( CH375Init( ) );  /* ��ʼ��CH375 */
}

#endif

#ifdef __cplusplus
}
#endif

#endif