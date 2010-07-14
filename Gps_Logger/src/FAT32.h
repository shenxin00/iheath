#ifndef __FAT32_H__
#define __FAT32_H__


/*******************************************************
	+-------------------------------------------+
	|FAT32文件系统								|
	+-------------------------------------------+
********************************************************/

// 用于计算簇的开始扇区
// 开始扇区 = (簇编号 - 根目录簇编号)x簇扇区数 + 根目录扇区编号
#define SOC(c) (((c - pArg->FirstDirClust)*(pArg->SectorsPerClust)) + pArg->FirstDirSector)


//位于0 扇区
//FAT32中对BPB的定义如下 一共占用90个字节		
struct FAT32_BPB
{
	UINT8	BS_jmpBoot[3];		//跳转指令				offset: 0
	UINT8	BS_OEMName[8];		//						offset: 3
	UINT8	BPB_BytesPerSec[2];	//每扇区字节数			offset:11
	UINT8	BPB_SecPerClus[1];	//每簇扇区数 			offset:13
	UINT8	BPB_RsvdSecCnt[2];	//保留扇区数目			offset:14
	UINT8	BPB_NumFATs[1];		//此卷中FAT表数			offset:16
	UINT8	BPB_RootEntCnt[2];	//FAT32为0				offset:17
	UINT8	BPB_TotSec16[2];	//FAT32为0				offset:19
	UINT8	BPB_Media[1];		//存储介质				offset:21
	UINT8	BPB_FATSz16[2];		//FAT32为0				offset:22
	UINT8	BPB_SecPerTrk[2];	//磁道扇区数 			offset:24
	UINT8	BPB_NumHeads[2];	//磁头数 				offset:26
	UINT8	BPB_HiddSec[4];		//FAT区前隐扇区数		offset:28
	UINT8	BPB_TotSec32[4];	//该卷总扇区数			offset:32
	UINT8	BPB_FATSz32[4];		//一个FAT表扇区数		offset:36
	UINT8	BPB_ExtFlags[2];	//FAT32特有				offset:40
	UINT8	BPB_FSVer[2];		//FAT32特有				offset:42
	UINT8	BPB_RootClus[4];	//根目录簇号 			offset:44
	UINT8	BPB_FSInfo[2];		//保留扇区FSINFO扇区数	offset:48
	UINT8	BPB_BkBootSec[2];	//通常为6				offset:50
	UINT8	BPB_Reserved[12];	//扩展用 				offset:52
	UINT8	BS_DrvNum[1];		//						offset:64
	UINT8	BS_Reserved1[1];	//						offset:65
	UINT8	BS_BootSig[1];		//						offset:66
	UINT8	BS_VolID[4];		//						offset:67
	UINT8	BS_FilSysType[11];	//						offset:71
	UINT8	BS_FilSysType1[8];	//"FAT32    "			offset:82
};

//FAT32的文件系统信息结构
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


//FAT32中对文件项的定义如下 一共占用32个字节
struct direntry 
{
	UINT8 deName[8];			// 文件名，不足部分以空格(0x20)补充		offset:
	UINT8 deExtension[3];		// 扩展名，不足部分以空格(0x20)补充		offset:
	UINT8 deAttributes;			// 文件属性								offset:
	UINT8 deLowerCase;			// 0									offset:
	UINT8 deCHundredth;			// 世纪									offset:
	UINT8 deCTime[2];			// 创建时间								offset:
	UINT8 deCDate[2];			// 创建日期								offset:
	UINT8 deADate[2];			// 访问日期								offset:
	UINT8 deHighClust[2];		// 开始簇的高字							offset:
	UINT8 deMTime[2];			// 最近的修改时间						offset:
	UINT8 deMDate[2];			// 最近的修改日期						offset:
	UINT8 deLowCluster[2];		// 开始簇的低字							offset:
	UINT8 deFileSize[4];		// 文件大小								offset:
}

//FAT分区表表项4个字节
struct FAT32_FAT_Item
{
	UINT8 Item[4];
};
//FAT分区表 1扇区=128x4字节=512字节
struct FAT32_FAT
{
	struct FAT32_FAT_Item Items[128];
};



//FAT32初始化时初始参数装入如下结构体中
struct FAT32_Init_Arg
{
	UINT8	BPB_Sector_No;		//BPB所在扇区号
	UINT32	Total_Size;			//总容量
	UINT32	Total_Sector;		//总扇区数
	UINT32	SectorsPerClust;	//每簇的扇区数
	UINT32	BytesPerSector;		//每个扇区的字节数
	UINT32	FATsectors;			//FAT表所占扇区数
	UINT32	FirstFATSector;		//第一个FAT表所在扇区
	UINT32	FirstDirClust;		//根目录的开始簇
	UINT32	FirstDirSector;		//根目录的开始扇区
	
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

// 文件信息
struct FileInfoStruct
{
	UINT8			FileName[12];		//文件名
	UINT32			FileStartCluster;	//文件的开始簇

	UINT32			FileCurCluster;		//文件的当前簇
	UINT32			FileSize;			
	UINT32			FileCurSector;		//文件的当前扇区
	UINT16			FileCurPos;			//文件在当前扇区中的位置
	UINT32			FileCurOffset;		//文件的当前偏移量
	UINT32			Rec_Sec;			//文件的文件/目录项所在的扇区
	UINT16			nRec;				//文件的文件/目录项所在扇区中的位置

	UINT8			FileAttr;			//文件属性
	struct Time		FileCreateTime;		//文件的创建时间
	struct Date		FileCreateDate;		//文件的创建日期
	struct Time		FileMTime;			//文件的修改时间
	struct Date		FileMDate;			//文件的修改日期
	struct Date		FileADate;			//文件的访问日期
};

	
	
	
	
	
	
#endif // __FAT32_H__

