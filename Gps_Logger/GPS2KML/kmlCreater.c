#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmlCreater.h"

#define EEPROM_MESSAGE_SIZE 			1024
 

int main(int argc, char *argv[])
{
    char src_file[64];
    char dst_file[64];  
	
    FILE * gpsPt;
	FILE * kmlPt;

	if(argc != 2)
	{
			printf("paramater error!\n");
			return -1;
	}
	
    strcpy(src_file,argv[1]);
    strcpy(dst_file,argv[1]);
    strcat(src_file,".dat");
    strcat(dst_file,".kml");
 
	gpsPt = fopen(src_file,"r");
	kmlPt = fopen(dst_file,"w+t");
		
	if(gpsPt==NULL)
	{
		printf("Can't find the GPS data file!\n");
		return -1;
	}
	else
	{
		printf("Success to open the GPS data file!\n");
	}
	if(kmlPt==NULL)
	{
		printf("Can't creat the kml file!\n");
		return -1;
	}
	else
	{
		printf("Success to creat GPS.kml!\n");
	}
//======================================================================
	kmlCreat(gpsPt,kmlPt);
//======================================================================
	if(fclose(gpsPt)==EOF)
	{
		printf("Error when close the file");
		return -1;
	}
	else
		fprintf(stdout,"Success to close the GPSdata!\n");
	if(fclose(kmlPt)==EOF)
	{
		printf("Error when close the GPS.kml\n");
		return -1;
	}
	else
	{
		printf("Success to close the GPS.kml!\n");
    }
    
	return 0;
}

int kmlCreat(FILE * gpsFilePt,FILE * kmlFilePt)
{
	int i;
	unsigned int kmlRecordLength=0;
	char temp[LINE_SIZE],tempFinal[LINE_SIZE*3]={0};
//===================================================================
#if 0
	for(i=0;i<3;i++)
	{
		fgets(temp,LINE_SIZE,gpsFilePt);
	}
	for(i=0;i<2;i++)
	{
		strcat(tempFinal,"\t\t\t");
		fgets(temp,LINE_SIZE,gpsFilePt);
		strcat(tempFinal,temp);
	}
	fscanf(gpsFilePt,"Total:\t%u\trecord\n",&kmlRecordLength);
	sprintf(temp,"\t\t\tTotal:\t%u\trecord\n",kmlRecordLength);
	strcat(tempFinal,temp);
	fgets(temp,LINE_SIZE,gpsFilePt);
#endif
   strcat(tempFinal,"\t\t\t");
   strcat(tempFinal,"is a test\n");
//===================================================================
	kmlCreatHeader(kmlFilePt,tempFinal);
	//kmlCreatData(gpsFilePt,kmlFilePt,kmlRecordLength);
	kmlCreatData(gpsFilePt,kmlFilePt,30);
	
	kmlCreatTail(kmlFilePt);
	return 0;
}

int kmlCreatHeader(FILE * kmlFilePt,char * kmlDescription)
{
	fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",kmlFilePt);
	fputs("<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n",kmlFilePt);
	fputs("<Document>\n",kmlFilePt);
	fputs("\t<name>GPS.kml</name>\n",kmlFilePt);
	fputs("\t<Folder>\n",kmlFilePt);
	fputs("\t\t<name>GPS</name>\n",kmlFilePt);
	fputs("\t\t<description>\n",kmlFilePt);
	fputs(kmlDescription,kmlFilePt);
	fputs("\t\t</description>\n",kmlFilePt);
	fputs("\t\t<name>GPS</name>\n",kmlFilePt);
	fputs("\t\t<open>1</open>\n",kmlFilePt);
	return 0;
}

int kmlCreatTail(FILE * kmlFilePt)
{
	fputs("\t</Folder>\n",kmlFilePt);
	fputs("</Document>\n",kmlFilePt);
	fputs("</kml>\n",kmlFilePt);
	return 0;
}

int kmlCreatData(FILE * gpsFilePt,FILE * kmlFilePt,unsigned int length)
{
	float latitude,longitutude,speed,course,magicDec,
			latitudeArray[EEPROM_MESSAGE_SIZE]={0},longitutudeArray[EEPROM_MESSAGE_SIZE]={0};
	char temp[LINE_SIZE],latitudeNS,longitudeEW,magicDecEW;
	int UTCTime,UTCdate,count,num=1;
	
	float f_utctime;
	char valid;
#if 0	
	for(count=0;count<length;count++)
	{
#else                                     
	while(fgets(temp,LINE_SIZE,gpsFilePt) != NULL)
	{
#endif
		
#if 0
//1:	034516,V,0000.0000,N,00000.0000,E,0.000,0.000,240705,0.000,E,Ù#
		sscanf(temp,"%d:\t%d,%*c,%f,%c,%f,%c,%f,%f,%d,%f,%c**",&num,&UTCTime,
					&latitude,&latitudeNS,
					&longitutude,&longitudeEW,
					&speed,&course,&UTCdate,
					&magicDec,&magicDecEW
				);
#else
//$GPRMC,083545.622,A,3541.2538,N,13949.6541,E,0.54,326.16,200810,,,A*62
		sscanf(temp+7,"%f,%c,%f,%c,%f,%c,%f,%f,%d**",
                    &f_utctime,&valid,
					&latitude,&latitudeNS,
					&longitutude,&longitudeEW,
					&speed,&course,&UTCdate
				);


#endif
		fputs("\t\t<Placemark>\n",kmlFilePt);
		fprintf(kmlFilePt,"\t\t\t<name>%d</name>\n",num);
		fputs("\t\t\t<description>\n",kmlFilePt);
		num++;
#if 0		
		fprintf(kmlFilePt,"\t\t\t\t%d:\t$GPRMC,%d,%f,%c,%f,%c,%f,%f,%d,%f,%c\n",num,UTCTime,
					latitude,latitudeNS,
					longitutude,longitudeEW,
					speed,course,UTCdate,
					magicDec,magicDecEW
				);
#else
		fprintf(kmlFilePt,"\t\t\t\t%d:\t$GPRMC,%d,%f,%c,%f,%c,%f,%f,%d\n",num,UTCTime,
					latitude,latitudeNS,
					longitutude,longitudeEW,
					speed,course,UTCdate
				);


#endif
		fputs("\t\t\t</description>\n",kmlFilePt);
		fputs("\t\t\t<Point>\n",kmlFilePt);
		longitutude/=100;
		longitutudeArray[count]=(int)longitutude+(longitutude-(int)longitutude)*100/60;
        longitutudeArray[count]=(longitudeEW=='E')?longitutudeArray[count]:-longitutudeArray[count];
		latitude/=100;
		latitudeArray[count]=(int)latitude+(latitude-(int)latitude)*100/60;
		latitudeArray[count]=(latitudeNS=='N')?latitudeArray[count]:-latitudeArray[count];
		fprintf(kmlFilePt,"\t\t\t\t<coordinates>%f,%f,0</coordinates>\n",
							longitutudeArray[count],
							latitudeArray[count]
				);
		fputs("\t\t\t</Point>\n",kmlFilePt);
		fputs("\t\t</Placemark>\n",kmlFilePt);
	}
	fputs("\t\t<Placemark>\n",kmlFilePt);
	fputs("\t\t<name>path line</name>\n",kmlFilePt);
	fputs("\t\t<LineString>\n",kmlFilePt);
	fputs("\t\t<coordinates>\n",kmlFilePt);
	for(count=0;count<length;count++)
	{	
		fprintf(kmlFilePt,"\t\t\t%f,%f,0\n",
							longitutudeArray[count],
							latitudeArray[count]
				);
	}
	fputs("\t\t</coordinates>\n",kmlFilePt);
	fputs("\t\t</LineString>\n",kmlFilePt);
	fputs("\t\t</Placemark>\n",kmlFilePt);
	return 0;
}
