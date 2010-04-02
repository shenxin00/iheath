
#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>

/*****************************************************/
/*
/*
/*
/*****************************************************/
#include "simlib.h"
#if 0
int main(){
	int i;
	int len;
	packetA_t	recvParam;
	packetB_t	sendParam;
	
	/* I/O fifo init	*/
	if(SBInitFIFO() == ERR_RTN){
		perror("initFIFO");
		return ERR_RTN;
	}
printf("SB START\n");
	while(1){
		recvFromSim(&recvParam);

printf("[recv]%d\n",recvParam.action);
		
		sendParam.stat = recvParam.action;
		//if(sendParam.stat == 'a'){
			sendToSim(&sendParam);
		//}
	}
}
#endif

////////////////////////////////////////////////////////////////
// 
//functon name:
// 
//Remarks:
// 
//
// Parameters:
// [in] null
// [out] null
//
// Return values:null
// 
///////////////////////////////////////////////////////////////////

#include "VxmlParser.h"

int main (int argc, char* args[]) {
	VxmlParser parser;
	
	string file ="gmcc_special.vxml";
	parser.DoParser(file);
	
	return 0;
}

