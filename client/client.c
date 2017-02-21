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
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("Error! socket failure!\n");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],&server_addr.sin_addr);
	if (connect(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) < 0){
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
			case LOG:
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
			case USERHELP:
				printf("\033[13;42H\033[38X");
				printf("\033[13;48H\43mCopyright @ 2016-2017,shen \033[0m\n");
				printf("\033[14;53H\033[43mAll Rights Reserve\033[0m\n");
				sleep(3);
				printf("\033[14;42H\033[38X");
				break;
			case USEREXIT:
				system("reset");
				exit(0);
			default:
				printf("\033[13;42H\033[38X");
				printf("\033[13;53H\033[41m您输入的命令有误！\033[0m\n");
				sleep(2);
		}
	}
	if(admin == 2){
		admin_start(temp.name);
	}
	else{
		client_start(temp.name);
	}

	pthread_create(&tid,NULL,thread_read,(void *)&sockfd);
	while(1){
		check_screen();
		time(&timep);
		strcpy(tm,ctime(&timep));
		tm[strlen(tm) - 1] = '\0';
		printf("\033[27;2H\033[100X\033[1A\033[100X\033[1A\033[100X\033[1A\033[100X");
		fflush(stdout);
		my_fgets(cmd,MAX,stdin);
		printf("\033[24;2H\033[100X");
		fflush(stdout);
		if(admin == 2){
			temp.cmd = analy_admin_cmd(cmd);
		}
		else{
			temp.cmd = analy_client_cmd(cmd);
		}
		strcpy(temp.time,tm);
		switch(temp.cmd)
		{
			case CHAT:
				chat_one(sockfd,&temp);
				sleep(1);
				break;
			case ALL:
				chat_all(sockfd,&temp);
				sleep(1);
				break;
			case SEE:
				handle_see_board();
				see(sockfd,&temp);
				sleep(3);
				break;
			case DATA:
				{
					char ch[MAX] = "no";
					printf("\033[1;1H\033[J");
					fflush(stdout);
					data(sockfd,&temp);
					sleep(3);
					printf("Please input yes\n");
					while(strcmp(ch,"yes") != 0){
						my_fgets(ch,MAX,stdin);
					}
					if(admin == 2){
						admin_start(temp.name);
					}
					else{
						client_start(temp.name);
					}
					sleep(2);
				}
				break;
			case FACE:
				face(sockfd,&temp);
				sleep(1);
				break;
			case HI:
				hi(sockfd,&temp);
				sleep(1);
				break;
			case PASSWORD:
				password(sockfd,&temp);
				sleep(3);
				break;
			case TRANS:
				trans(sockfd,&temp);
				sleep(5);
				break;
			case CHANGE:
				change(sockfd,&temp);
				sleep(1);
				break;
			case HELP:
				if(admin == 2){
					admin_start(temp.name);
				}
				else{
					client_start(temp.name);
				}
				sleep(1);
				break;
			case EXIT:
				exit_tell(sockfd,&temp);
				sleep(1);
				system("reset");
				exit(0);
			default:
				printf("您输入的命令有误！\n");
				sleep(1);
				break;
		}
	}
	close(sockfd);
	return 0;
}
