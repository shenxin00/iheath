#include "simlib.h"


void* thread_func(void *arg);
int handleClientAction();

int main(){
	int i;
	int len;


	pthread_t threadId;
	/* I/O fifo init	*/
	if(SimInitFIFO() == ERR_RTN){
		perror("initFIFO");	
		return ERR_RTN;
	}
    /* Watch SB Core output thread */
	
	if(pthread_create(&threadId,NULL,thread_func,NULL) !=0){
		perror("pthread_create");		
		return ERR_RTN;
	}
	
#ifdef DEBUG_SIM
cout<<"Sim start!"<<endl;
#endif

	while(1){
		/* wait phone client for connection*/
		handleClientAction();
		
	}    
}

int handleClientAction(){
	char action;
	packetA_t sendparam;
	struct FromSBParam param;
	
	action = getchar();
	// trim "\n" 
	if(action == 10){
		return OK_RTN;
	}MaruoBack
	
	sendparam.action = action;
	sendToSB(&sendparam);
	
	return OK_RTN;


}


void* thread_func(void *arg){;
	struct FromSBParam param;
	int len;

	while(1){
		memset(&param,0,sizeof(param));
		if(recvFromSB(&param) == ERR_RTN){
			sleep(100);
			continue;
		}

		printf("[sb_msg]:[%d],[%d],[%d],[%d],[%d],[%s],[%s]\n",
				param.type,
				param.channel,
				param.src,
				param.dest,
				param.stat,
				param.prompt,
				param.audio);
	}
}
