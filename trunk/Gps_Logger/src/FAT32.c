#include "FAT32.h"


/*******************************************************
	+-------------------------------------------+
	|FAT32�ļ�ϵͳ								|
	+-------------------------------------------+
********************************************************/


//ȫ�ֱ�������

//�������ݶ�д������
UINT8 FAT32_Buffer[512];
//��ʼ�������ṹ��ʵ��
struct FAT32_Init_Arg Init_Arg_Mmc;
struct FAT32_Init_Arg *pArg;
//pArg =&Init_Arg_Mmc;


struct direntry temp_rec;
INT8 temp_dir_name[13]; 
UINT32 temp_dir_cluster;
UINT32 temp_last_cluster;

/*********************************************************************************************************/
/*	�ڲ���������
/*********************************************************************************************************/
UINT8	FAT32_ReadSector(UINT32 addr,UINT8 *buf);
UINT8	FAT32_WriteSector(UINT32 addr,UINT8 *buf);
UINT32	FAT32_GetNextCluster(UINT32 LastCluster);

UINT32	LE2BE(UINT8 *dat,UINT8 len);
INT8	L2U(INT8 c);



/*********************************************************************************************************/
/*	�ⲿ��������
/*********************************************************************************************************/
/***********************************************************************
 - ����������FAT32�ļ�ϵͳ��ʼ��
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����FAT32_Init_Arg���͵Ľṹ��ָ�룬����װ��һЩ��Ҫ�Ĳ�����Ϣ��
             �Ա�����ʹ��     
 - ����˵������
 - ע����ʹ��znFATǰ����������Ǳ����ȱ����õģ����ܶ������Ϣװ�뵽
       argָ��Ľṹ���У�����������С����Ŀ¼��λ�á�FAT���С�ȵȡ�
       ��Щ�������󲿷���������DBR��BPB�У���˴˺�����Ҫ������DBR�Ĳ�������
 ***********************************************************************/
void FAT32_Init()
{
	struct FAT32_BPB *bpb;
	//��BPB���н���
	pArg->BPB_Sector_No = 0;					//BPB���ڵ������� Ĭ��:0
	
	//��ȡ0����
	FAT32_ReadSector(pArg->BPB_Sector_No,FAT32_Buffer);
	
	//�����ݻ�����ָ��תΪstruct FAT32_BPB ��ָ��
	bpb = (struct FAT32_BPB *)(FAT32_Buffer);
	
	//
	pArg->BytesPerSector	= LE2BE((bpb->BPB_BytesPerSec),2);	//װ��ÿ�����ֽ�����BytesPerSector��
	pArg->SectorsPerClust	= LE2BE((bpb->BPB_SecPerClus) ,1);	//װ��ÿ����������SectorsPerClust ��
	pArg->FirstFATSector	= LE2BE((bpb->BPB_RsvdSecCnt) ,2)+pArg->BPB_Sector_No;
																//װ���һ��FAT�������ŵ�FirstFATSector ��
	pArg->FATsectors		= LE2BE((bpb->BPB_FATSz32)    ,4);	//װ��FAT��ռ�õ���������FATsectors��
	pArg->FirstDirClust		= LE2BE((bpb->BPB_RootClus)   ,4);	//װ���Ŀ¼�غŵ�FirstDirClust��
	pArg->FirstDirSector	= (pArg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(pArg->FATsectors);
																//װ���һ��Ŀ¼������FirstDirSector��
	pArg->Total_Size		= (LE2BE((bpb->BPB_TotSec32)  ,4))*pArg->BytesPerSector;
																//��������Total_Size��

	//temp_last_cluster=Search_Last_Usable_Cluster();
	
	return;
}

/**************************************************************************
 - �����������ڸ�Ŀ¼�´���һ���ļ�/Ŀ¼��
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����pfi:ָ��FileInfoStruct���͵Ľṹ�壬����װ�ظմ������ļ�����Ϣ
                 Ҳ����˵�������������Ŀ¼����˽ṹ�岻�ᱻ����
             cluster:��cluster������д����ļ�/Ŀ¼�����ʵ��������Ŀ¼��
                 �����ļ���Ŀ¼������ͨ��FAT32_Enter_Dir����ȡĳһ��Ŀ¼�Ŀ�
                 ʼ��
             name:�ļ�/Ŀ¼������
             is_dir:ָʾҪ���������ļ�����Ŀ¼���ļ���Ŀ¼�Ĵ��������ǲ�ͬ��
                 1��ʾ����Ŀ¼ 0��ʾ�����ļ�
 - ����˵�����ɹ�����1��ʧ�ܷ���-1
 **************************************************************************/

UINT8 FAT32_Create_Rec(struct FileInfoStruct *pfi,UINT32 cluster,INT8 *name,UINT8 is_dir,UINT8 *ptd)
{

	UINT32 iSec,iFile,sec_temp;
	UINT32 new_clu,old_clu;
	
	UINT32 StartSector;
	struct direntry *pFile;
	INT8 temp_file_name[13];
	
	//��ȡ��Ŀ¼���ڴ�
	Cur_Clust = pArg->FirstDirClust;
	
	while(Cur_Clust != 0x0fffffff)
	{
		StartSector = SOC(Cur_Clust)
		
		//��������λ ������Ŀ¼���ڴ�
		for(iSec=StartSector;iSec<StartSector+pArg->SectorsPerClust;iSec++)
		{
			//��ȡ��������
			FAT32_ReadSector(iSec,FAT32_Buffer);
			for(iFile=0;iFile<pArg->BytesPerSector;iFile+=sizeof(struct direntry))
			{
				pFile = ((struct direntry *)(FAT32_Buffer+iFile));
				//���ļ�/Ŀ¼�����
				if((pFile->deName)[0]!=0){
					continue;
				}
				
				//����ļ���
				Fill_Rec_Inf(pFile,name,ptd)
				
				//��д��������
				FAT32_WriteSector(iSec,FAT32_Buffer);
				
				//on success return 0
				goto RTN_OK;
				
			}//iFile loop
			
		}//iSec loop
		
		old_clu = Cur_Clust;
		Cur_Clust = FAT32_GetNextCluster();
	}//Clust loop
	
	
	//Ŀ¼���ڴ���
	new_clu = FAT32_Find_Free_Clust();
	
	if(new_clu == 0){
		//on ERROR return 1
		return 1;
	}
	
	//�����ļ�/Ŀ¼��
	pFile = ((struct direntry *)(FAT32_Buffer);
	//����ļ���
	Fill_Rec_Inf(pFile,name,ptd);
	//����´�������
	iSec = SOC(new_clu);
	//д��������
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
 - �����������򿪸�Ŀ¼�µ�һ���ļ�
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����pfi: FileInfoStruct���͵Ľṹ��ָ�룬����װ���ļ��Ĳ�����Ϣ
              �����ļ��Ĵ�С���ļ������ơ��ļ��Ŀ�ʼ�صȵȣ��Ա�����ʹ��
             filename: �ļ���
 - ����˵����0���ɹ� 1���ļ�������
 - ע�����ļ����ɹ��кܶ�ԭ�򣬱����ļ������ڡ��ļ���ĳһ��Ŀ¼������
       ͨ������������������ļ�����С��item��ֵ�ȵ�
	   ͨ������£��ļ�����û��ͨ�����item��ֵ����ȡ0�Ϳ�����
**************************************************************************/
UINT8 FAT32_Open_File(struct FileInfoStruct *pfi,INT8 *filename)
{
	UINT32 iSec,iFile,sec_temp;
	UINT32 StartSector;
	struct direntry *pFile;
	INT8 temp_file_name[13];
	
	//��ȡ��Ŀ¼���ڴ�
	Cur_Clust = pArg->FirstDirClust;
	
	while(Cur_Clust != 0x0fffffff)
	{
		StartSector = SOC(Cur_Clust)
		
		//��������λ ������Ŀ¼���ڴ�
		for(iSec=StartSector;iSec<StartSector+pArg->SectorsPerClust;iSec++)
		{
			//��ȡ��������
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
/*	�ڲ���������
/*********************************************************************************************************/

/******************************************************************
 - ����������znFAT�Ĵ洢�豸�ײ������ӿڣ���ȡ�洢�豸��addr������
             512���ֽڵ����ݷ���buf���ݻ�������
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ���������洢�豸�ĵײ������Խӣ�
 - ����˵����addr:������ַ
             buf:ָ�����ݻ�����
 - ����˵����0��ʾ��ȡ�����ɹ�������ʧ��
 - ע����������������Ǿ������ϵ����ִ洢�豸����SD������Ч����U�̡�
       CF��ͨ���ڳ����ж�̬���л���ͬ���豸�������Ӷ�ʵ�ֶ��豸(��ͬ
	   ʱ�Զ��ִ洢�豸���в����������SD�������ļ���U�̵ȵ�)����ͬ
	   �������л���ֻ��Ҫ�ڳ����иı�Dev_No���ȫ�ֱ�����ֵ����
 ******************************************************************/

UINT8 FAT32_ReadSector(UINT32 addr,UINT8 *buf) 
{
	return mmcReadSector(addr,buf);
}

/******************************************************************
 - ����������znFAT�Ĵ洢�豸�ײ������ӿڣ���buf���ݻ������е�512��
             �ֽڵ�����д�뵽�洢�豸��addr������
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ���������洢�豸�ĵײ������Խӣ�
 - ����˵����addr:������ַ
             buf:ָ�����ݻ�����
 - ����˵����0��ʾ��ȡ�����ɹ�������ʧ��
 - ע����
 ******************************************************************/

UINT8 FAT32_WriteSector(UINT32 addr,UINT8 *buf)
{
	return mmcWriteSector(addr, buf);
}

/***********************************************************************
 - ���������������һ���صĴغ�
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����LastCluster:��׼�غ�  
 - ����˵����LastClutster����һ�صĴغ�
 - ע�������һ�صĴغţ�����ƾ��FAT��������¼�Ĵ�����ϵ��ʵ�ֵ�
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
 - ����������Ѱ�ҿ��õĿ��д�
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵������
 - ����˵��������ҵ��˿��дأ����ؿ��дصĴغţ����򷵻�0
 - ע��Ѱ�ҿ��д��Ǵ���Ŀ¼/�ļ��Լ����ļ�д�����ݵĻ�����������ܺܿ��Ѱ
       �ҵ����дأ���ô����Ŀ¼/�ļ��Լ����ļ�д��������Щ����Ҳ��ȽϿ졣
       �������Ǿ�������ʼ�Ĵ�����ȥѰ�ң�����ʹ���˶����������㷨���Դ�
       ���Ϻõ�Ч����������д�û���ҵ������п��ܾ�˵���洢�豸�Ѿ�û�пռ�
       ��
 **************************************************************************/
UINT32 FAT32_Find_Free_Clust(unsigned char flag)
{
	UINT32 iClu,iSec;
	UINT32 last_cluster;
	struct FAT32_FAT *pFAT;
	
	//��������FAT����
	for(iSec=pArg->FirstFATSector;iSec<pArg->FirstFATSector+pArg->FATsectors;iSec++)
	{
		FAT32_ReadSector(iSec,FAT32_Buffer);
		pFAT=(struct FAT32_FAT *)FAT32_Buffer;
		//��������FAT����
		for(iClu=0;iClu<pArg->BytesPerSector/4;iClu++)
		{
			//���дؼ��
			if(LE2BE((UINT8 *)(&((pFAT->Items))[iClu]),4)==0)
			{
				return 128*(iSec-pArg->FirstFATSector)+iClu;
			}
		}
	}
	
	return 0;
}

/**************************************************************************
 - ��������������FAT��
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����cluster:Ҫ���µĴ����
             dat:Ҫ����Ӧ�Ĵ������Ϊdat
 - ����˵������
 - ע�������ļ�д�������ݺ���Ҫ��FAT����и����Ա��������ݵĴ�����ϵ 
       ɾ���ļ���ʱ��Ҳ��Ҫ�����ļ��Ĵ����������������ļ��Ĵ�����ϵ
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
 - ��������������ļ�/Ŀ¼��
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����prec:ָ��һ��direntry���͵Ľṹ�壬���Ľṹ����FAT32���ļ�/
             Ŀ¼��Ľṹ
             name:�ļ���Ŀ¼������
             is_dir:ָʾ����ļ�/Ŀ¼�����ļ�����Ŀ¼���ֱ�����ʵ���ļ���
             Ŀ¼�Ĵ��� 1��ʾ����Ŀ¼ 0��ʾ�����ļ�
 - ����˵������
 - ע�����ﴴ���ļ���Ŀ¼�ķ����ǣ��Ƚ��ļ���Ŀ¼����Ϣ��䵽һ���ṹ���У�
       Ȼ���ٽ�����ṹ�������д�뵽�洢�豸����Ӧ����������Ӧλ����ȥ����
       ����������ļ���Ŀ¼�Ĵ�����
       ������ļ���Ŀ¼����Ϣʱ���ļ���Ŀ¼���״ز�û�����ȥ������ȫ0
 **************************************************************************/

void Fill_Rec_Inf(struct direntry *prec,INT8 *name,UINT8 *ptd)
{
	UINT8 i=0,len=0;
	
	UINT16 temp;

	while(name[len]!='.' && name[len]!=0) len++;
	// �ļ��������㲿���Կո�(0x20)����
	for(i=0;i<len;i++)
	{
		(prec->deName)[i]=L2U(name[i]);
	}
	for(;i<8;i++)
	{
		(prec->deName)[i]=' ';
	}
	// ��չ�������㲿���Կո�(0x20)����	
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
	
	// �ļ�����
	(prec->deAttributes)	= 0x20;
	// 0
	(prec->deLowerCase)		= 0x0;
	// ����
	(prec->deCHundredth)	= 0x15;
	
	// ����ʱ��	
	temp=MAKE_FILE_TIME(ptd[3],ptd[4],ptd[5]);
	(prec->deCTime)[0]			= temp;
	(prec->deCTime)[1]			= temp>>8;
	// ������޸�ʱ��
	(prec->deMTime)[0]			= temp;
	(prec->deMTime)[1]			= temp>>8;
	
	// ��������
	temp=MAKE_FILE_DATE(ptd[0],ptd[1],ptd[2]);
	(prec->deCDate)[0]			= temp;
	(prec->deCDate)[1]			= temp>>8;
	// ��������
	(prec->deADate)[0]			= temp;
	(prec->deADate)[1]			= temp>>8;
	// ������޸�����
	(prec->deMDate)[0]			= temp;
	(prec->deMDate)[1]			= temp>>8;
	
	// ��ʼ�صĸ���	
	(prec->deHighClust)[0]		= 0;
	(prec->deHighClust)[1]		= 0;
	// ��ʼ�صĵ���	
	(prec->deLowCluster)[0]		= 0;
	(prec->deLowCluster)[1]		= 0;

	// �ļ���С		
	for(i=0;i<4;i++)
	{
		(prec->deFileSize)[i]	=0;
	}
	
}


/******************************************************************
 - ����������С��ת��ˣ���LittleEndianתBigEndian
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����dat:ָ��ҪתΪ��˵��ֽ�����
             len:ҪתΪ��˵��ֽ����г���
 - ����˵����תΪ���ģʽ���ֽ���������������
 - ע�����磺С��ģʽ��       0x33 0x22 0x11 0x00  (���ֽ���ǰ)
             תΪ���ģʽ��Ϊ 0x00 0x11 0x22 0x33  (���ֽ���ǰ)
             ��������ֵΪ   0x00112233
             (CISC��CPUͨ����С�˵ģ�����FAT32Ҳ���ΪС�ˣ�����Ƭ��
              ����RISC��CPU��ͨ����˵���Ǵ�˵ģ�������Ҫ�����������
              �ڵĴ�Ŵ�����е��������ܵõ���ȷ����ֵ)
 ******************************************************************/

UINT32 LE2BE(UINT8 *dat,UINT8 len)
{
	UINT32 temp=0;
	UINT32 fact=1;
	UINT8  i=0;
	for(i=0;i<len;i++)
	{
		temp+=dat[i]*fact; //�����ֽڳ�����Ӧ��Ȩֵ���ۼ�
		fact*=256; //����Ȩֵ
	}
	return temp;
}

/******************************************************************
 - ������������С���ַ�תΪ��д
 - ����ģ�飺znFAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����c:Ҫת��Ϊ��д���ַ�            
 - ����˵����Ҫת�����ֽڵ���Ӧ�Ĵ�д�ַ�
 - ע��ֻ��Сд�ַ���Ч���������a~z��Сд�ַ�����ֱ�ӷ���
 ******************************************************************/

INT8 L2U(INT8 c)
{
	if(c>='a' && c<='z') return c+'A'-'a';
	else return c;
}

