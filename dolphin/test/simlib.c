
#include "simlib.h"


#define TO_SB_FIFO			"/tmp/to_sb_fifo"
#define FROM_SB_FIFO		"/tmp/from_sb_fifo"

int ToSimFd = -1;
int FromSimFd = -1;
int ToSBFd = -1;
int FromSBFd = -1;


/* init FIFO for API */ 
int SBInitFIFO()
{
	/*create fifo*/
	if( access(TO_SB_FIFO,F_OK) == -1 ) {
		if(mkfifo(TO_SB_FIFO,0777)==-1){
			perror("TO SB FIFO.");
			return ERR_RTN;
		}
	}
	if( access(FROM_SB_FIFO,F_OK) == -1 ) {
		if(mkfifo(FROM_SB_FIFO,0777)==-1){
			perror("FROM SB FIFO.");
			return ERR_RTN;
		}
	}

	/*open fifo*/
	if((FromSimFd=open(TO_SB_FIFO,O_RDONLY))==-1){
		perror("FROM SIM FD.");
		return ERR_RTN;
	}
	/*open fifo*/
	if((ToSimFd=open(FROM_SB_FIFO,O_WRONLY))==-1){
		perror("TO SIM FD.");
		return ERR_RTN;
	}
	
	return OK_RTN;
}
/* init FIFO for API */ 
int SimInitFIFO()
{
	/*create fifo*/
	if( access(TO_SB_FIFO,F_OK) == -1 ) {
		if(mkfifo(TO_SB_FIFO,0777)==-1){
			perror("TO SB FIFO.");
			return ERR_RTN;
		}
	}
	if( access(FROM_SB_FIFO,F_OK) == -1 ) {
		if(mkfifo(FROM_SB_FIFO,0777)==-1){
			perror("FROM SB FIFO.");
			return ERR_RTN;
		}
	}
	/*open fifo*/
	if((ToSBFd=open(TO_SB_FIFO,O_WRONLY))==-1){
		perror("TO SB FD.");
		return ERR_RTN;
	}
	/*open fifo*/
	if((FromSBFd=open(FROM_SB_FIFO,O_RDONLY))==-1){
		perror("FROM SB FD.");
		return ERR_RTN;
	}

	return OK_RTN;
}

int sendToSim(packetB_t * param){
	int len;
	len = write(ToSimFd,param,sizeof(packetB_t));

	if(len != sizeof(packetB_t)){
		perror("sendToSim.");
		return ERR_RTN;	
	}
#ifdef DEBUG_SIM
printf("[%s]:len=%d\n",__FUNCTION__,len);
#endif
	return OK_RTN;
}

int sendToSB(packetA_t * param){
	int len;
	len = write(ToSBFd,param,sizeof(packetA_t));

	if(len != sizeof(packetA_t)){
		perror("sendToSB.");
		return ERR_RTN;	
	}
#ifdef DEBUG_SIM
printf("[%s]:len=%d\n",__FUNCTION__,len);
#endif
	return OK_RTN;
}

int recvFromSB(packetB_t * param){    
	int len;
	int recvlen;
	char *recvp=NULL;
	len=0;
	recvlen=0;
	recvp = (char *)param;
	while(1){
		len = read(FromSBFd,recvp,sizeof(packetB_t));
		if(len >0){	
			recvlen += len;
			recvp += len;
			if(recvlen == sizeof(packetB_t)){
				break;
			}
		}
	}
#ifdef DEBUG_SIM
printf("[%s]:len=%d\n",__FUNCTION__,recvlen);
#endif

	return OK_RTN;
}

int recvFromSim(packetA_t * param){
	int len;
	int recvlen;
	char *recvp=NULL;
	len=0;
	recvlen=0;
	recvp = (char *)param;
	while(1){
		len = read(FromSimFd,recvp,sizeof(packetA_t));
		if(len >0){	
			recvlen += len;
			recvp += len;
			if(recvlen == sizeof(packetA_t)){
				break;
			}
		}
	}

#ifdef DEBUG_SIM
printf("[%s]:len=%d\n",__FUNCTION__,recvlen);
#endif
	return OK_RTN;
}

