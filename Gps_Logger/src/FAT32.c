#include "FAT32.h"


/*******************************************************
	+-------------------------------------------+
	|FAT32文件系统								|
	+-------------------------------------------+
********************************************************/


//全局变量定义

//扇区数据读写缓冲区
UINT8 FAT32_Buffer[512];
//初始化参数结构体实体
struct FAT32_Init_Arg Init_Arg_Mmc;
struct FAT32_Init_Arg *pArg;
//pArg =&Init_Arg_Mmc;


struct direntry temp_rec;
INT8 temp_dir_name[13]; 
UINT32 temp_dir_cluster;
UINT32 temp_last_cluster;

/*********************************************************************************************************/
/*	内部函数声明
/*********************************************************************************************************/
UINT8	FAT32_ReadSector(UINT32 addr,UINT8 *buf);
UINT8	FAT32_WriteSector(UINT32 addr,UINT8 *buf);
UINT32	FAT32_GetNextCluster(UINT32 LastCluster);

UINT32	LE2BE(UINT8 *dat,UINT8 len);
INT8	L2U(INT8 c);



/*********************************************************************************************************/
/*	外部函数定义
/*********************************************************************************************************/
/***********************************************************************
 - 功能描述：FAT32文件系统初始化
 - 隶属模块：znFAT文件系统模块
 - 函数属性：外部，使用户使用
 - 参数说明：FAT32_Init_Arg类型的结构体指针，用于装载一些重要的参数信息，
             以备后面使用     
 - 返回说明：无
 - 注：在使用znFAT前，这个函数是必须先被调用的，将很多参数信息装入到
       arg指向的结构体中，比如扇区大小、根目录的位置、FAT表大小等等。
       这些参数绝大部分是来自于DBR的BPB中，因此此函数主要在作对DBR的参数解析
 ***********************************************************************/
void FAT32_Init()
{
	struct FAT32_BPB *bpb;
	//对BPB进行解析
	pArg->BPB_Sector_No = 0;					//BPB所在的扇区号 默认:0
	
	//读取0扇区
	FAT32_ReadSector(pArg->BPB_Sector_No,FAT32_Buffer);
	
	//将数据缓冲区指针转为struct FAT32_BPB 型指针
	bpb = (struct FAT32_BPB *)(FAT32_Buffer);
	
	//
	pArg->BytesPerSector	= LE2BE((bpb->BPB_BytesPerSec),2);	//装入每扇区字节数到BytesPerSector中
	pArg->SectorsPerClust	= LE2BE((bpb->BPB_SecPerClus) ,1);	//装入每簇扇区数到SectorsPerClust 中
	pArg->FirstFATSector	= LE2BE((bpb->BPB_RsvdSecCnt) ,2)+pArg->BPB_Sector_No;
																//装入第一个FAT表扇区号到FirstFATSector 中
	pArg->FATsectors		= LE2BE((bpb->BPB_FATSz32)    ,4);	//装入FAT表占用的扇区数到FATsectors中
	pArg->FirstDirClust		= LE2BE((bpb->BPB_RootClus)   ,4);	//装入根目录簇号到FirstDirClust中
	pArg->FirstDirSector	= (pArg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(pArg->FATsectors);
																//装入第一个目录扇区到FirstDirSector中
	pArg->Total_Size		= (LE2BE((bpb->BPB_TotSec32)  ,4))*pArg->BytesPerSector;
																//总容量到Total_Size中

	//temp_last_cluster=Search_Last_Usable_Cluster();
	
	return;
}

/**************************************************************************
 - 功能描述：在根目录下创建一个文件/目录项
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：pfi:指向FileInfoStruct类型的结构体，用于装载刚创建的文件的信息
                 也就是说，如果创建的是目录，则此结构体不会被更新
             cluster:在cluster这个簇中创建文件/目录项，用于实现在任意目录下
                 创建文件或目录，可以通过FAT32_Enter_Dir来获取某一个目录的开
                 始簇
             name:文件/目录的名称
             is_dir:指示要创建的是文件还是目录，文件与目录的创建方法是不同的
                 1表示创建目录 0表示创建文件
 - 返回说明：成功返回1，失败返回-1
 **************************************************************************/

UINT8 FAT32_Create_Rec(struct FileInfoStruct *pfi,UINT32 cluster,INT8 *name,UINT8 is_dir,UINT8 *ptd)
{

	UINT32 iSec,iFile,sec_temp;
	UINT32 new_clu,old_clu;
	
	UINT32 StartSector;
	struct direntry *pFile;
	INT8 temp_file_name[13];
	
	//获取根目录所在簇
	Cur_Clust = pArg->FirstDirClust;
	
	while(Cur_Clust != 0x0fffffff)
	{
		StartSector = SOC(Cur_Clust)
		
		//以扇区单位 搜索根目录所在簇
		for(iSec=StartSector;iSec<StartSector+pArg->SectorsPerClust;iSec++)
		{
			//读取扇区内容
			FAT32_ReadSector(iSec,FAT32_Buffer);
			for(iFile=0;iFile<pArg->BytesPerSector;iFile+=sizeof(struct direntry))
			{
				pFile = ((struct direntry *)(FAT32_Buffer+iFile));
				//空文件/目录项检索
				if((pFile->deName)[0]!=0){
					continue;
				}
				
				//填充文件项
				Fill_Rec_Inf(pFile,name,ptd)
				
				//回写扇区内容
				FAT32_WriteSector(iSec,FAT32_Buffer);
				
				//on success return 0
				goto RTN_OK;
				
			}//iFile loop
			
		}//iSec loop
		
		old_clu = Cur_Clust;
		Cur_Clust = FAT32_GetNextCluster();
	}//Clust loop
	
	
	//目录所在簇满
	new_clu = FAT32_Find_Free_Clust();
	
	if(new_clu == 0){
		//on ERROR return 1
		return 1;
	}
	
	//生成文件/目录项
	pFile = ((struct direntry *)(FAT32_Buffer);
	//填充文件项
	Fill_Rec_Inf(pFile,name,ptd);
	//获得新簇扇区号
	iSec = SOC(new_clu);
	//写扇区内容
	FAT32_WriteSector(iSec,FAT32_Buffer);	

RTN_OK:
	strcpy(pfi->FileName,name);
	pfi->FileStartCluster=0;
	pfi->FileCurCluster=0;
	pfi->FileSize=0;
	pfi->FileCurSector=0;
	pfi->FileCurPos=0;
	pfi->FileCurOffset=0;
	pfi->Rec_Sec=temp_sec;
	pfi->nRec=pFile;
	pfi->FileAttr=pFile.deAttributes;

	//on success return 0
	return 0;
	
	

	
	
	
 UINT32 iSec,iRec,temp_sec,temp_clu,new_clu,i,old_clu;
 UINT8 flag=0;
 UINT16 temp_Rec;
 struct direntry *pRec;
 Fill_Rec_Inf(&temp_rec,name,is_dir,ptd);
 do
 {
  old_clu=cluster;
  temp_sec=SOC(cluster);
  for(iSec=temp_sec;iSec<temp_sec+pArg->SectorsPerClust;iSec++)
  {
   FAT32_ReadSector(iSec,FAT32_Buffer);
   for(iRec=0;iRec<pArg->BytesPerSector;iRec+=sizeof(struct direntry))
   {
    pRec=(struct direntry *)(FAT32_Buffer+iRec);
	if((pRec->deName)[0]==0)
	{
	 flag=1;
	 if(is_dir)
	 {
	  if(!(new_clu=FAT32_Find_Free_Clust(0))) return -1;
	  FAT32_Modify_FAT(new_clu,0x0fffffff);
	  (temp_rec.deHighClust)[0]=(new_clu&0x00ff0000)>>16;
      (temp_rec.deHighClust)[1]=(new_clu&0xff000000)>>24;
      (temp_rec.deLowCluster)[0]=(new_clu&0x000000ff);
      (temp_rec.deLowCluster)[1]=(new_clu&0x0000ff00)>>8;
	 }
	 
	 FAT32_ReadSector(iSec,FAT32_Buffer);
	 for(i=0;i<sizeof(struct direntry);i++)
	 {
	  ((UINT8 *)pRec)[i]=((UINT8 *)(&temp_rec))[i];
	 }
	 FAT32_WriteSector(iSec,FAT32_Buffer);
	 temp_sec=iSec;
	 temp_Rec=iRec;
	 iRec=pArg->BytesPerSector;
	 iSec=temp_sec+pArg->SectorsPerClust;
	}
   }
  }
 }while(!flag && (cluster=FAT32_GetNextCluster(cluster))!=0x0fffffff);
 
 if(!flag)
 {
  if(!(temp_clu=FAT32_Find_Free_Clust(0))) return -1;
  FAT32_Modify_FAT(temp_clu,0x0fffffff);
  FAT32_Modify_FAT(old_clu,temp_clu);
  temp_sec=SOC(temp_clu);
  temp_Rec=0;
  FAT32_ReadSector(temp_sec,FAT32_Buffer);
  if(is_dir)
  {
   if(!(new_clu=FAT32_Find_Free_Clust(0))) return -1;
   FAT32_Modify_FAT(new_clu,0x0fffffff);
   FAT32_ReadSector(temp_sec,FAT32_Buffer);
   (temp_rec.deHighClust)[0]=(new_clu&0x00ff0000)>>16;
   (temp_rec.deHighClust)[1]=(new_clu&0xff000000)>>24;
   (temp_rec.deLowCluster)[0]=(new_clu&0x000000ff);
   (temp_rec.deLowCluster)[1]=(new_clu&0x0000ff00)>>8;
  }
  for(i=0;i<sizeof(struct direntry);i++)
  {
   FAT32_Buffer[i]=((UINT8 *)(&temp_rec))[i]; 
  }
  FAT32_WriteSector(temp_sec,FAT32_Buffer);
 }
 if(is_dir)
 {
  FAT32_Empty_Cluster(new_clu);

  Fill_Rec_Inf(&temp_rec,".",1,ptd);
  (temp_rec.deHighClust)[0]=(new_clu&0x00ff0000)>>16;
  (temp_rec.deHighClust)[1]=(new_clu&0xff000000)>>24;
  (temp_rec.deLowCluster)[0]=(new_clu&0x000000ff);
  (temp_rec.deLowCluster)[1]=(new_clu&0x0000ff00)>>8;
  for(i=0;i<sizeof(struct direntry);i++)
  {
   FAT32_Buffer[i]=((UINT8 *)(&temp_rec))[i]; 
  }
  Fill_Rec_Inf(&temp_rec,"..",1,ptd);
  if(cluster==pArg->FirstDirClust)
  {
   (temp_rec.deHighClust)[0]=0;
   (temp_rec.deHighClust)[1]=0;
   (temp_rec.deLowCluster)[0]=0;
   (temp_rec.deLowCluster)[1]=0;
  }
  else
  {
   (temp_rec.deHighClust)[0]=(cluster&0x00ff0000)>>16;
   (temp_rec.deHighClust)[1]=(cluster&0xff000000)>>24;
   (temp_rec.deLowCluster)[0]=(cluster&0x000000ff);
   (temp_rec.deLowCluster)[1]=(cluster&0x0000ff00)>>8;
  }
    
  for(i=sizeof(struct direntry);i<2*sizeof(struct direntry);i++)
  {
   FAT32_Buffer[i]=((UINT8 *)(&temp_rec))[i-sizeof(struct direntry)]; 
  }
  for(;i<pArg->BytesPerSector;i++)
  {
   FAT32_Buffer[i]=0;
  }		
  temp_sec=SOC(new_clu);
  FAT32_WriteSector(temp_sec,FAT32_Buffer);
 }
 else
 {
  strcpy(pfi->FileName,name);
  pfi->FileStartCluster=0;
  pfi->FileCurCluster=0;
  pfi->FileSize=0;
  pfi->FileCurSector=0;
  pfi->FileCurPos=0;
  pfi->FileCurOffset=0;
  pfi->Rec_Sec=temp_sec;
  pfi->nRec=temp_Rec;

  pfi->FileAttr=temp_rec.deAttributes;
 }
 FAT32_Find_Free_Clust(1);
 return 1;
}

/**************************************************************************
 - 功能描述：打开根目录下的一个文件
 - 隶属模块：znFAT文件系统模块
 - 函数属性：外部，使用户使用
 - 参数说明：pfi: FileInfoStruct类型的结构体指针，用来装载文件的参数信息
              比如文件的大小、文件的名称、文件的开始簇等等，以备后面使用
             filename: 文件名
 - 返回说明：0：成功 1：文件不存在
 - 注：打开文件不成功有很多原因，比如文件不存在、文件的某一级目录不存在
       通配情况下满足条件的文件项数小于item的值等等
	   通常情况下，文件名中没有通配符，item的值我们取0就可以了
**************************************************************************/
UINT8 FAT32_Open_File(struct FileInfoStruct *pfi,INT8 *filename)
{
	UINT32 iSec,iFile,sec_temp;
	UINT32 StartSector;
	struct direntry *pFile;
	INT8 temp_file_name[13];
	
	//获取根目录所在簇
	Cur_Clust = pArg->FirstDirClust;
	
	while(Cur_Clust != 0x0fffffff)
	{
		StartSector = SOC(Cur_Clust)
		
		//以扇区单位 搜索根目录所在簇
		for(iSec=StartSector;iSec<StartSector+pArg->SectorsPerClust;iSec++)
		{
			//读取扇区内容
			FAT32_ReadSector(iSec,FAT32_Buffer);
			for(iFile=0;iFile<pArg->BytesPerSector;iFile+=sizeof(struct direntry))
			{
				pFile = ((struct direntry *)(FAT32_Buffer+iFile));
				
				if(!(pFile->deAttributes&0x20)){
					continue;
				}
				FAT32_toFileName(pFile->deName,temp_file_name);
				
				if(strcmp(filename,temp_file_name) != 0){
					continue;
				}

				Cur_Clust=LE2BE(pFile->deLowCluster,2)+LE2BE(pFile->deHighClust,2)*65536;

				strcpy(pfi->FileName,temp_file_name);
				
				pfi->FileSize				= LE2BE(pFile->deFileSize,4);
				pfi->FileStartCluster		= LE2BE(pFile->deLowCluster,2)+LE2BE(pFile->deHighClust,2)*65536;
				pfi->FileCurCluster			= pfi->FileStartCluster;
				pfi->FileCurSector			= SOC(pfi->FileStartCluster);
				pfi->FileCurPos				= 0;
				pfi->FileCurOffset			= 0;
				pfi->Rec_Sec				= iSec;
				pfi->nRec					= iFile;

				pfi->FileAttr				= pFile->deAttributes;
				sec_temp					= LE2BE(pFile->deCTime,2);
				(pfi->FileCreateTime).sec	= (sec_temp&0x001f)*2;
				(pfi->FileCreateTime).min	= ((sec_temp>>5)&0x003f);
				(pfi->FileCreateTime).hour	= ((sec_temp>>11)&0x001f);
				sec_temp					= LE2BE(pFile->deCDate,2);
				(pfi->FileCreateDate).day	= ((sec_temp)&0x001f);
				(pfi->FileCreateDate).month	= ((sec_temp>>5)&0x000f);
				(pfi->FileCreateDate).year	= ((sec_temp>>9)&0x007f)+1980;

				sec_temp					= LE2BE(pFile->deMTime,2);
				(pfi->FileMTime).sec		= (sec_temp&0x001f)*2;
				(pfi->FileMTime).min		= ((sec_temp>>5)&0x003f);
				(pfi->FileMTime).hour		= ((sec_temp>>11)&0x001f);
				sec_temp					= LE2BE(pFile->deMDate,2);
				(pfi->FileMDate).day		= ((sec_temp)&0x001f);
				(pfi->FileMDate).month		= ((sec_temp>>5)&0x000f);
				(pfi->FileMDate).year		= ((sec_temp>>9)&0x007f)+1980;

				sec_temp					= LE2BE(pFile->deADate,2);
				(pfi->FileADate).day		= ((sec_temp)&0x001f);
				(pfi->FileADate).month		= ((sec_temp>>5)&0x000f);
				(pfi->FileADate).year		= ((sec_temp>>9)&0x007f)+1980;

				//on success return 0
				return 0;
				
			}//iFile loop
		}//iSec loop
		
		Cur_Clust = FAT32_GetNextCluster();
	}//Clust loop
	
	//on file don't exist return 1
	return 1;
	
}




/*********************************************************************************************************/
/*	内部函数定义
/*********************************************************************************************************/

/******************************************************************
 - 功能描述：znFAT的存储设备底层驱动接口，读取存储设备的addr扇区的
             512个字节的数据放入buf数据缓冲区中
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部（用于与存储设备的底层驱动对接）
 - 参数说明：addr:扇区地址
             buf:指向数据缓冲区
 - 返回说明：0表示读取扇区成功，否则失败
 - 注：这里加入了天狼星精华板上的三种存储设备，即SD卡（有效）、U盘、
       CF卡通过在程序中动态的切换不同的设备驱动，从而实现多设备(即同
	   时对多种存储设备进行操作，比如从SD卡拷贝文件到U盘等等)，不同
	   驱动的切换，只需要在程序中改变Dev_No这个全局变量的值即可
 ******************************************************************/

UINT8 FAT32_ReadSector(UINT32 addr,UINT8 *buf) 
{
	return mmcReadSector(addr,buf);
}

/******************************************************************
 - 功能描述：znFAT的存储设备底层驱动接口，将buf数据缓冲区中的512个
             字节的数据写入到存储设备的addr扇区中
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部（用于与存储设备的底层驱动对接）
 - 参数说明：addr:扇区地址
             buf:指向数据缓冲区
 - 返回说明：0表示读取扇区成功，否则失败
 - 注：略
 ******************************************************************/

UINT8 FAT32_WriteSector(UINT32 addr,UINT8 *buf)
{
	return mmcWriteSector(addr, buf);
}

/***********************************************************************
 - 功能描述：获得下一个簇的簇号
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：LastCluster:基准簇号  
 - 返回说明：LastClutster的下一簇的簇号
 - 注：获得下一簇的簇号，就是凭借FAT表中所记录的簇链关系来实现的
 ***********************************************************************/

UINT32 FAT32_GetNextCluster(UINT32 LastCluster)
{
	UINT32 temp;
	struct FAT32_FAT *pFAT;
	struct FAT32_FAT_Item *pFAT_Item;
	temp=((LastCluster/128)+pArg->FirstFATSector);
	FAT32_ReadSector(temp,FAT32_Buffer);
	pFAT=(struct FAT32_FAT *)FAT32_Buffer;
	pFAT_Item=&((pFAT->Items)[LastCluster%128]);
	return LE2BE((UINT8 *)pFAT_Item,4);
}

/**************************************************************************
 - 功能描述：寻找可用的空闲簇
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：无
 - 返回说明：如果找到了空闲簇，返回空闲簇的簇号，否则返回0
 - 注：寻找空闲簇是创建目录/文件以及向文件写入数据的基础，它如果能很快的寻
       找到空闲簇，那么创建目录/文件以及向文件写入数据这些操作也会比较快。
       所以我们绝不会从最开始的簇依次去寻找，而是使用了二分搜索的算法，以达
       到较好的效果。如果空闲簇没有找到，很有可能就说明存储设备已经没有空间
       了
 **************************************************************************/
UINT32 FAT32_Find_Free_Clust(unsigned char flag)
{
	UINT32 iClu,iSec;
	UINT32 last_cluster;
	struct FAT32_FAT *pFAT;
	
	//遍历所有FAT扇区
	for(iSec=pArg->FirstFATSector;iSec<pArg->FirstFATSector+pArg->FATsectors;iSec++)
	{
		FAT32_ReadSector(iSec,FAT32_Buffer);
		pFAT=(struct FAT32_FAT *)FAT32_Buffer;
		//遍历所有FAT表项
		for(iClu=0;iClu<pArg->BytesPerSector/4;iClu++)
		{
			//空闲簇检查
			if(LE2BE((UINT8 *)(&((pFAT->Items))[iClu]),4)==0)
			{
				return 128*(iSec-pArg->FirstFATSector)+iClu;
			}
		}
	}
	
	return 0;
}

/**************************************************************************
 - 功能描述：更新FAT表
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：cluster:要更新的簇项号
             dat:要将相应的簇项更新为dat
 - 返回说明：无
 - 注：在向文件写入了数据后，需要对FAT表进行更表，以表明新数据的簇链关系 
       删除文件的时候，也需要将该文件的簇项进行清除，销毁文件的簇链关系
 **************************************************************************/

void FAT32_Modify_FAT(UINT32 cluster,UINT32 dat)
{
	FAT32_ReadSector(pArg->FirstFATSector+(cluster*4/pArg->BytesPerSector),FAT32_Buffer);
	FAT32_Buffer[((cluster*4)%pArg->BytesPerSector)+0]=dat&0x000000ff;
	FAT32_Buffer[((cluster*4)%pArg->BytesPerSector)+1]=(dat&0x0000ff00)>>8;
	FAT32_Buffer[((cluster*4)%pArg->BytesPerSector)+2]=(dat&0x00ff0000)>>16;
	FAT32_Buffer[((cluster*4)%pArg->BytesPerSector)+3]=(dat&0xff000000)>>24;
	FAT32_WriteSector(pArg->FirstFATSector+(cluster*4/pArg->BytesPerSector),FAT32_Buffer);
	
	return;
}


/**************************************************************************
 - 功能描述：填充文件/目录项
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：prec:指向一个direntry类型的结构体，它的结构就是FAT32中文件/
             目录项的结构
             name:文件或目录的名称
             is_dir:指示这个文件/目录项是文件还是目录，分别用来实现文件、
             目录的创建 1表示创建目录 0表示创建文件
 - 返回说明：无
 - 注：这里创建文件或目录的方法是，先将文件或目录的信息填充到一个结构体中，
       然后再将这个结构体的数据写入到存储设备的相应的扇区的相应位置上去，这
       样就完成了文件或目录的创建。
       在填充文件或目录的信息时，文件或目录的首簇并没有填进去，而是全0
 **************************************************************************/

void Fill_Rec_Inf(struct direntry *prec,INT8 *name,UINT8 *ptd)
{
	UINT8 i=0,len=0;
	
	UINT16 temp;

	while(name[len]!='.' && name[len]!=0) len++;
	// 文件名，不足部分以空格(0x20)补充
	for(i=0;i<len;i++)
	{
		(prec->deName)[i]=L2U(name[i]);
	}
	for(;i<8;i++)
	{
		(prec->deName)[i]=' ';
	}
	// 扩展名，不足部分以空格(0x20)补充	
	for(i=0;i<3;i++)
	{
		(prec->deExtension)[i]=' ';
	}
	
	if(name[len]=='.')
	{
		while(name[len]!=0)
		{
			(prec->deExtension)[i++]=L2U(name[len]);
			len++;
		}
	}
	
	// 文件属性
	(prec->deAttributes)	= 0x20;
	// 0
	(prec->deLowerCase)		= 0x0;
	// 世纪
	(prec->deCHundredth)	= 0x15;
	
	// 创建时间	
	temp=MAKE_FILE_TIME(ptd[3],ptd[4],ptd[5]);
	(prec->deCTime)[0]			= temp;
	(prec->deCTime)[1]			= temp>>8;
	// 最近的修改时间
	(prec->deMTime)[0]			= temp;
	(prec->deMTime)[1]			= temp>>8;
	
	// 创建日期
	temp=MAKE_FILE_DATE(ptd[0],ptd[1],ptd[2]);
	(prec->deCDate)[0]			= temp;
	(prec->deCDate)[1]			= temp>>8;
	// 访问日期
	(prec->deADate)[0]			= temp;
	(prec->deADate)[1]			= temp>>8;
	// 最近的修改日期
	(prec->deMDate)[0]			= temp;
	(prec->deMDate)[1]			= temp>>8;
	
	// 开始簇的高字	
	(prec->deHighClust)[0]		= 0;
	(prec->deHighClust)[1]		= 0;
	// 开始簇的低字	
	(prec->deLowCluster)[0]		= 0;
	(prec->deLowCluster)[1]		= 0;

	// 文件大小		
	for(i=0;i<4;i++)
	{
		(prec->deFileSize)[i]	=0;
	}
	
}


/******************************************************************
 - 功能描述：小端转大端，即LittleEndian转BigEndian
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：dat:指向要转为大端的字节序列
             len:要转为大端的字节序列长度
 - 返回说明：转为大端模式后，字节序列所表达的数据
 - 注：比如：小端模式的       0x33 0x22 0x11 0x00  (低字节在前)
             转为大端模式后为 0x00 0x11 0x22 0x33  (高字节在前)
             所表达的数值为   0x00112233
             (CISC的CPU通常是小端的，所以FAT32也设计为小端，而单片机
              这种RISC的CPU，通常来说都是大端的，所以需要这个函数将字
              节的存放次序进行调整，才能得到正确的数值)
 ******************************************************************/

UINT32 LE2BE(UINT8 *dat,UINT8 len)
{
	UINT32 temp=0;
	UINT32 fact=1;
	UINT8  i=0;
	for(i=0;i<len;i++)
	{
		temp+=dat[i]*fact; //将各字节乘以相应的权值后累加
		fact*=256; //更新权值
	}
	return temp;
}

/******************************************************************
 - 功能描述：将小字字符转为大写
 - 隶属模块：znFAT文件系统模块
 - 函数属性：内部
 - 参数说明：c:要转换为大写的字符            
 - 返回说明：要转换的字节的相应的大写字符
 - 注：只对小写字符有效，如果不是a~z的小写字符，将直接返回
 ******************************************************************/

INT8 L2U(INT8 c)
{
	if(c>='a' && c<='z') return c+'A'-'a';
	else return c;
}

