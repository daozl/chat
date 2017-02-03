/*****************************************
 *客户端功能函数所需要的头文件
 *Author:zldao
 *Date:2017.1.23
 ****************************************/
#ifndef HEAD_H__
#define HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sqlite3.h>
#include <termios.h>
#include <assert.h>
#include <netdb.h>

#define MAX		1024
#define PORT	8888

struct chat
{
	char name[20];            //用户名
	char password[20];        //用户名密码
	int cmd;                  //命令选项
	int revert;
	char toname[20];
	char msg[1024];
	int flag;
	int sockfd;
	char time[50];
	char filename[20];
};

extern int row;
extern int nsee;

enum cmd
{
	ERROR = -1,
	REG = 1,
	LOG,
	HELP,
	EXIT,
	USERHELP,
	USEREXIT,
	CAHT,
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
	PASSWORKNO,
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
