#ifndef __HEAD__
#define __HEAD__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sqlite3.h"
#include "signal.h"
#include "time.h"
#define MAX 1024
#define PORT 8888

struct chat
{
	char name[20];
	char password[20];
	int cmd;
	int revert;
	char toname[20];
	char msg[1024];
	int flag;
	int sockfd;
	char time[50];
	char filename[20];
};

enum cmd
{
	ERROR = -1,
	REG = 1,
	LOG,
	HELP,
	EXIT,
	USERHELP,
	USEREXIT,
	CHAT,
	ALL,
	SEE,
	DATA,
	FACE,
	HI,
	TRANS,
	PASSWORD,
	CHANGE,
	KICK,
	SHUT,
	REMOVE,
	CANCEL
};

enum revert
{
	REGOK = 1,
	REGNO,
	PASSWORDOK,
	PASSWORDNO,
	USERIN,
	USEROUT,
	ONLINEIN,
	ONLINEOUT,
	MYFLAGOK,
	MYFLAGNO,
	TOFLAGOK,
	TOFLAGNO,
	CHATOK,
	ALLOK,
	SEEOK,
	DATAOK,
	TRANSOK,
	KICKOK
};

#endif
