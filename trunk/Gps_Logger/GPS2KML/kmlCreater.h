#define 	LINE_SIZE	100

int kmlCreat(FILE * gpsFilePt,FILE * kmlFilePt);
int kmlCreatHeader(FILE * kmlFilePt,char * kmlDescription);
int kmlCreatTail(FILE * kmlFilePt);
int kmlCreatData(FILE * gpsFilePt,FILE * kmlFilePt,unsigned int length);
