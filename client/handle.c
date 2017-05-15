#include "head.h"
#include "handle.h"

void wait_dian()
{
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf(".\n");
}

void my_fgets(char *buf,int bufsize,FILE *stream)
{
	fgets(buf,bufsize,stream);
	buf[strlen(buf) - 1] = '\0';
}

void check_screen()
{
	if(row >= 22){
		row;
		while (row > 9){
			printf("\033[%d;2H\033[95X",row--);
			fflush(stdout);
		}
		printf("\033[%d;2H\033[95X",row);
		printf("\033[24;2H");
		fflush(stdout);
	}
}

void handle_see_board()
{
	for(nsee = 9; nsee <= 21; nsee++){
		printf("\033[%d;105H\033[11X",nsee);
		fflush(stdout);
	}
	nsee = 9;
}

void reg(int sockfd,struct chat *temp)
{
	char *password;
	char *password1;

	reg_start();
	my_fgets(temp->name,20,stdin);
	printf("\033[60C");
	password = (char *)secret_password();
	printf("\n");
	printf("\033[60C");
	password1 = (char *)secret_password();
	printf("\n");
	if(strcmp(password,password1) == 0){
		printf("\n");
		printf("\033[12;47H 正在注册中，请稍等一会儿");
		wait_dian();
		strcpy(temp->password,password);
		write(sockfd,temp,sizeof(struct chat));
		memset(temp,0,sizeof(struct chat));
		temp->revert = -999;
		read(sockfd,temp,sizeof(struct chat));
		printf("\033[12;42H\033[38X");
		if(REGOK == temp->revert){
			printf("\033[12;47H 您已经注册成功，欢迎您的使用! \n");
			printf("\033[13:50H 请牢记您的ID号吗 : %d\n",temp->flag);
		}
		else if(REGNO == temp->revert){
			printf("\033[12;50H\033[41m 该用户名已经备注测！\033[0m\n");
		}
		else{
			printf("\033[12;50H\033[41m 接收到错误的服务器消息！\033[0m\n");
		}
	}
	else{
		printf("\033[12;50H\033[41m 两次输入的密吗不相同！\033[0m\n");
	}
}

void Log(int sockfd,struct chat *temp)
{
	char *password;
	
	log_start();
	my_fgets(temp->name,20,stdin);
	printf("\033[60C");
	password = (char *)secret_password();
	printf("\n");
	strcpy(temp->password,password);
	write(sockfd,temp,sizeof(struct chat));
	printf("\n");
	printf("\033[11;47H 正在登录中，请稍等一会儿");
	wait_dian();
}

void chat_one(int sockfd, struct chat *temp)
{
	printf("\033[24;2H请输入对方用户名：");
	my_fgets(temp->toname,20,stdin);
	printf("\033[25;2H请输入发送的内容：");
	my_fgets(temp->msg,1024,stdin);
	write(sockfd,temp,sizeof(struct chat));
	printf("\033[%d;2H你对 %s 说： %s (%s)\n",row++,temp->toname,temp->msg,temp->time);
}

void chat_all(int sockfd,struct chat *temp)
{
	strcpy(temp->toname,"所有人");
	printf("\033[24;2H请输入发送的内容：");
	my_fgets(temp->msg,1024,stdin);
	write(sockfd,temp,sizeof(struct chat));
	printf("\033[%d;2H你对 %s 说：%s (%s)\n",row++,temp->toname,temp->msg,temp->time);
}
void see(int sockfd,struct chat *temp)
{
	write(sockfd,temp,sizeof(struct chat));
}

void data(int sockfd,struct chat *temp)
{
	write(sockfd,temp,sizeof(struct chat));
}

void password(int sockfd,struct chat *temp)
{
	char *password;
	char *password1;

	fflush(stdout);
	printf("\033[24;2H请输入密码（小于二十个字）：");
	password = (char *)secret_password();
	printf("\n");
	printf("\033[25;2H请再次输入密码（小于二十个字）：");
	password1 = (char *)secret_password();
	printf("\n");
	if(strcmp(password,password1) == 0){
		strcpy(temp->password,password);
		write(sockfd,temp,sizeof(struct chat));
	}
	else{
		printf("\033[26;2H两次输入的密码不相同！\n");
	}
}

void trans(int sockfd,struct chat *temp)
{
	FILE *fp = NULL;
	char filename[40];
	char ch;
	int i = 0;

	printf("\033[24;2H请输入对方用户名：");
	my_fgets(temp->toname,20,stdin);
	printf("\033[25;2H请输入需要发送的文件名（文件名小于40字节，文件大小小于1MB）：");
	my_fgets(filename,40,stdin);
	if((fp = fopen(filename, "r")) == NULL){
		printf("\033[26;2H该文件不存在！\n");
	}
	else{
		strcpy(temp->filename,filename);
		while((ch = getc(fp)) != EOF){
			temp->msg[i++] = ch;
			if(i >= 1023)
				break;
		}
		temp->msg[i] = '\0';
		write(sockfd,temp,sizeof(struct chat));
		fclose(fp);
	}
}

void exit_tell(int sockfd,struct chat *temp)
{
	char *msg = "下线啦！";
	memset(temp->msg,0,1024);
	strcpy(temp->toname,"所有人");
	strcat(temp->msg,temp->name);
	strcat(temp->msg,msg);
	temp->cmd = ALL;
	write(sockfd,temp,sizeof(struct chat));
	printf("\033[%d;2H你对 %s 说：%s (%s)\n",row++,temp->toname,temp->msg,temp->time);
}







