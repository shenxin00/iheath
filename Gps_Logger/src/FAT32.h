#ifndef __FAT32_H__
#define __FAT32_H__


/*******************************************************
	+-------------------------------------------+
	|FAT32�ļ�ϵͳ								|
	+-------------------------------------------+
********************************************************/

// ���ڼ���صĿ�ʼ����
// ��ʼ���� = (�ر�� - ��Ŀ¼�ر��)x�������� + ��Ŀ¼�������
#define SOC(c) (((c - pArg->FirstDirClust)*(pArg->SectorsPerClust)) + pArg->FirstDirSector)


//λ��0 ����
//FAT32�ж�BPB�Ķ������� һ��ռ��90���ֽ�		
struct FAT32_BPB
{
	UINT8	BS_jmpBoot[3];		//��תָ��				offset: 0
	UINT8	BS_OEMName[8];		//						offset: 3
	UINT8	BPB_BytesPerSec[2];	//ÿ�����ֽ���			offset:11
	UINT8	BPB_SecPerClus[1];	//ÿ�������� 			offset:13
	UINT8	BPB_RsvdSecCnt[2];	//����������Ŀ			offset:14
	UINT8	BPB_NumFATs[1];		//�˾���FAT����			offset:16
	UINT8	BPB_RootEntCnt[2];	//FAT32Ϊ0				offset:17
	UINT8	BPB_TotSec16[2];	//FAT32Ϊ0				offset:19
	UINT8	BPB_Media[1];		//�洢����				offset:21
	UINT8	BPB_FATSz16[2];		//FAT32Ϊ0				offset:22
	UINT8	BPB_SecPerTrk[2];	//�ŵ������� 			offset:24
	UINT8	BPB_NumHeads[2];	//��ͷ�� 				offset:26
	UINT8	BPB_HiddSec[4];		//FAT��ǰ��������		offset:28
	UINT8	BPB_TotSec32[4];	//�þ���������			offset:32
	UINT8	BPB_FATSz32[4];		//һ��FAT��������		offset:36
	UINT8	BPB_ExtFlags[2];	//FAT32����				offset:40
	UINT8	BPB_FSVer[2];		//FAT32����				offset:42
	UINT8	BPB_RootClus[4];	//��Ŀ¼�غ� 			offset:44
	UINT8	BPB_FSInfo[2];		//��������FSINFO������	offset:48
	UINT8	BPB_BkBootSec[2];	//ͨ��Ϊ6				offset:50
	UINT8	BPB_Reserved[12];	//��չ�� 				offset:52
	UINT8	BS_DrvNum[1];		//						offset:64
	UINT8	BS_Reserved1[1];	//						offset:65
	UINT8	BS_BootSig[1];		//						offset:66
	UINT8	BS_VolID[4];		//						offset:67
	UINT8	BS_FilSysType[11];	//						offset:71
	UINT8	BS_FilSysType1[8];	//"FAT32    "			offset:82
};

//FAT32���ļ�ϵͳ��Ϣ�ṹ
struct FSInfo 
{
	UINT8 Head[4];
	UINT8 Resv1[480];
	UINT8 Sign[4];
	UINT8 Free_Cluster[4];
	UINT8 Last_Cluster[4];
	UINT8 Resv2[14];
	UINT8 Tail[2];
};


//FAT32�ж��ļ���Ķ������� һ��ռ��32���ֽ�
struct direntry 
{
	UINT8 deName[8];			// �ļ��������㲿���Կո�(0x20)����		offset:
	UINT8 deExtension[3];		// ��չ�������㲿���Կո�(0x20)����		offset:
	UINT8 deAttributes;			// �ļ�����								offset:
	UINT8 deLowerCase;			// 0									offset:
	UINT8 deCHundredth;			// ����									offset:
	UINT8 deCTime[2];			// ����ʱ��								offset:
	UINT8 deCDate[2];			// ��������								offset:
	UINT8 deADate[2];			// ��������								offset:
	UINT8 deHighClust[2];		// ��ʼ�صĸ���							offset:
	UINT8 deMTime[2];			// ������޸�ʱ��						offset:
	UINT8 deMDate[2];			// ������޸�����						offset:
	UINT8 deLowCluster[2];		// ��ʼ�صĵ���							offset:
	UINT8 deFileSize[4];		// �ļ���С								offset:
}

//FAT���������4���ֽ�
struct FAT32_FAT_Item
{
	UINT8 Item[4];
};
//FAT������ 1����=128x4�ֽ�=512�ֽ�
struct FAT32_FAT
{
	struct FAT32_FAT_Item Items[128];
};



//FAT32��ʼ��ʱ��ʼ����װ�����½ṹ����
struct FAT32_Init_Arg
{
	UINT8	BPB_Sector_No;		//BPB����������
	UINT32	Total_Size;			//������
	UINT32	Total_Sector;		//��������
	UINT32	SectorsPerClust;	//ÿ�ص�������
	UINT32	BytesPerSector;		//ÿ���������ֽ���
	UINT32	FATsectors;			//FAT����ռ������
	UINT32	FirstFATSector;		//��һ��FAT����������
	UINT32	FirstDirClust;		//��Ŀ¼�Ŀ�ʼ��
	UINT32	FirstDirSector;		//��Ŀ¼�Ŀ�ʼ����
	
};

struct Date
{
	UINT16	year;
	UINT8	month;
	UINT8	day;
};

struct Time
{
	UINT8	hour;
	UINT8	min;
	UINT8	sec;
};

// �ļ���Ϣ
struct FileInfoStruct
{
	UINT8			FileName[12];		//�ļ���
	UINT32			FileStartCluster;	//�ļ��Ŀ�ʼ��

	UINT32			FileCurCluster;		//�ļ��ĵ�ǰ��
	UINT32			FileSize;			
	UINT32			FileCurSector;		//�ļ��ĵ�ǰ����
	UINT16			FileCurPos;			//�ļ��ڵ�ǰ�����е�λ��
	UINT32			FileCurOffset;		//�ļ��ĵ�ǰƫ����
	UINT32			Rec_Sec;			//�ļ����ļ�/Ŀ¼�����ڵ�����
	UINT16			nRec;				//�ļ����ļ�/Ŀ¼�����������е�λ��

	UINT8			FileAttr;			//�ļ�����
	struct Time		FileCreateTime;		//�ļ��Ĵ���ʱ��
	struct Date		FileCreateDate;		//�ļ��Ĵ�������
	struct Time		FileMTime;			//�ļ����޸�ʱ��
	struct Date		FileMDate;			//�ļ����޸�����
	struct Date		FileADate;			//�ļ��ķ�������
};

	
	
	
	
	
	
#endif // __FAT32_H__

