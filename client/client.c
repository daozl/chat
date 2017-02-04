#include "head.h"
#include "pack.h"

int row = 9;
int nsee = 9;

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in server_addr;
	struct hostent *host;
	struct chat temp;
	char cmd[MAX];
	int login = 0;
	int admin;
	pthread_t tid;
	time_t timep;
	char tm[MAX];

	if(argc != 2){
		printf("Error! The correct format is \n./client 127.0.0.1\n");
		exit(1);
	}
	if ((host = gethostbyname(argv[1])) == NULL){
		printf("Error! gethostbyname failure!\n");
		exit(1);
	}
	if((sockfd = socket(AF_INET,SOCK_STERM,0)) < 0){
		printf("Error! socket failure!\n");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

	if (connect(sockfd,(struct sockfd *)&server_addr,sizeof(struct sockaddr)) < 0){
		printf("Error! connect failure!\n");
		exit(1);
	}
	start();
	memset(&temp,0,sizeof(struct chat));
	while(!login){
		admin = 0;
		printf("\033[13;42H\033[38X");
		printf("\033[13;50H 请输入相应的命令：");
		my_fgets(cmd,MAX,stdin);
		temp.cmd = analy_start_cmd(cmd);
		
		switch(temp.cmd)
		{
			case REG:
				reg(sockfd,&temp);
				sleep(3);
				printf("\033[12;42H\033[38X");
				break;
			case Log:
				Log(sockfd,&temp);
				if(strcmp(temp.name,"admin")){
					admin++;
				}
				memset(&temp,0,sizeof(struct chat));
				read(sockfd,&temp,sizeof(struct chat));
				printf("\033[11;42H\033[38X");
				if(temp.revert == PASSWORDOK){
					admin++;
					printf("\033[11;47H 您已经登录成功，欢迎您的使用！\n");
					login = 1;
				}
				else if(temp.revert == PASSWORDNO){
					printf("\033[11;50H\033[41m 密码错误或用户名不存在！\033[0m\n");
				}
				else if(temp.revert == ONLINEIN){
					printf("\033[11;52H\033[41m 该用户已经登录！\033[0m\n");
				}
				else{
					printf("\033[11;50H\033[41m 接受到错误的服务器消息！\033[0m\n");
				}
				break;
		}
	}
}





























