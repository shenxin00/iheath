#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>



#include "comm.h"

/*From pbx*/
#define NEW_CONNECTION		10
#define CANCEL_CONNECTION	11
#define USR_ACTION			12
#define TIMEOUT_EVENT		13
#define NOINPUT_EVENT		14

/*TO Pbx*/
#define PROMPT_TEXT			21
#define AUDIO_SRC			22
#define RES_STAT			23
#define CUT_CONTNECTION		24




#define PROMPT_LEN      256
#define AUDIO_LEN       256
#define TEXT_LEN 		256





#define NONE_CONNECTION     -1

//#define DBG


/**/
typedef struct ToSBParam{
	int type;
	int channel;
	int src;
	int dest;
	int action;
}packetA_t;


typedef struct FromSBParam{
	int type;
	int channel;
	int src;
	int dest;
	int stat;
	char prompt[PROMPT_LEN];
	char audio[AUDIO_LEN];
}packetB_t;

extern int SBInitFIFO();
extern int SimInitFIFO();
extern int sendToSim(struct FromSBParam * param);
extern int sendToSB(struct ToSBParam * param);
extern int recvFromSB(struct FromSBParam * param);
extern int recvFromSim(struct ToSBParam * param);




