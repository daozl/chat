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
		print("\033[12;47H 正在注册中，请稍等一会儿");
		wait_dian();
		strcpy(temp->password,password);
		write(sockfd,temp,sizeof(struct chat));
		memset(temp,0,sizeof(struct chat));
		temp->revert = -999;
		read(sockfd,temp,sizeof(sizeof(struct chat)));
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

void log(int sockfd,struct chat *temp);
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
	printf("\033[%s;2H你对 %s 说：%s (%s)\n",row++,temp->toname,temp-msg,temp->time);
}
void see(int sockfd,struct chat *temp)
{
	write(sockfd,temp,sizeof(struct chat));
}

void data(int sockfd,struct chat *temp)
{
	write(sockfd,temp,sizeof(struct chat));
}

void face(int sockfd,struct chat *temp)
{
	char *face1 = "^_^";
	char *face2 = "@.@";
	char *face3 = "$.$";
	char *face4 = "+_+":
	char *face5 = "=_=";
	char *face6 = "o.O";
	char *face7 = "T.T";
	int n = 0;
	char face[10];
	char buf[20];
	char ch;
	printf("|1 %s |2 %s |3 %s |4 %s |5 %s |6 %s |7 %s |\n",face1,face2, face3, face4,face5,face6,face7);
	printf("\033[25;2H请选择一个表情（输入序号）：");
	scanf("%d",&n);
	while((ch = getchar()) != '\n' && ch != EOF);
	switch (n)
	{
		case 1:
			strcpy(face,face1);
			break;
		case 2:
			strcpy(face,face2);
			break;
		case 3:
			strcpy(face,face3);
			break;
		case 4:
			strcpy(face,face4);
			break;
		case 5:
			strcpy(face,face5);
			break;
		case 6:
			strcpy(face,face6);
			break;
		case 7:
			strcpy(face,face7);
			break;
		default:
			printf("\033[26;2H该表情不存在！\n");
			exit(1);
	}
	printf("\033[26;2H请选择私聊还是群聊（chat or all）: ");
	my_fgets(buf,20,stdin);
	if (strcmp(buf,"chat") == 0){
		printf("\033[27;2H请输入对方用户名：");
		my_fgets(temp->toname,20,stdin);
		strcpy(temp->msg,face);
		temp->cmd = CHAT;
		write(sockfd,temp,sizeof(struct chat));
		printf("\033[%d;2H你对 %s 说：%s (%s)\n",row++,temp->toname,temp->msg,temp->time);
	}
	else if(strcmp(buf,"all")){
		strcpy(temp->toname,"所有人");
		strcpy(temp->msg,face);
		temp->cmd = ALL;
		write(sockfd,temp,sizeof(struct chat));
		printf("\033[%d;2H你对 %s 说：%s (%s)\n",row++,temp->toname,temp->msg,temp->time);
	}
	else{
		printf("\033[27;2H非法指令！\n");
	}
	print("\033[5;8H%s\n",face);
}

void hi(int sockfd,struct chat *temp)
{

}























