#include "head.h"
#include "start.h"

void start()
{
	system("reset");
	printf("\n\n\n");
	printf("\t\t\t\t\t\033[47m________________________________________\033[0m\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|         *欢迎使用本聊天系统*         |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|            1.注册用户 reg            |\n");
	printf("\t\t\t\t\t|            2.登录系统 log            |\n");
	printf("\t\t\t\t\t|            3.关于系统 help           |\n");
	printf("\t\t\t\t\t|            4.退出系统 exit           |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|______________________________________|\n");
}

void reg_start()
{
	printf("\033[1;1H\033[J");
	printf("\n\n\n");
	printf("\t\t\t\t\t\033[47m________________________________________\033[0m\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|          *欢迎进入注册系统*          |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|    请输入用户名：                    |\n");
	printf("\t\t\t\t\t|      请输入密码：                    |\n");
	printf("\t\t\t\t\t|  请再次输入密码：                    |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|     *用户名和密码均不可超过二十个字！|\n");
	printf("\t\t\t\t\t|______________________________________|\n");
	printf("\033[9A");
	printf("\033[60C");
}

void log_start()
{
	printf("\033[1;1H\033[J");
	printf("\n\n\n");
	printf("\t\t\t\t\t\033[47m________________________________________\033[0m\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|          *欢迎进入登录系统*          |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|    请输入用户名：                    |\n");
	printf("\t\t\t\t\t|      请输入密码：                    |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|                                      |\n");
	printf("\t\t\t\t\t|______________________________________|\n");
	printf("\033[7A");
	printf("\033[60C");
}

void admin_start(char *name)
{
	printf("\033[1;1H\033[J");
	printf("______________________________________________________________________________________________________________________\n");
	printf("|  ___________                                                                                                       |\n");
	printf("|  | 每日心情| 功能服务：| help 重置 | chat 私聊 | all 群聊  | see  查看在线用户| data 查看历史记录 |                |\n");
	printf("|  |         |           | exit 退出 | face 表情 | hi  常用语| trans 发送文件   | password 修改密码 |                |\n");
	printf("|  | ( =_= ) |                                                                                                       |\n");
	printf("|  |_________| \033[43m管理员 %s\033[0m\n", name);
	printf("|\033[32m--------------------------------------------------------------------------------------------------------------------\033[0m|\n");
	printf("|                                                                                                   |  \033[42m当前在线用户\033[0m  |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|\033[32m--------------------------------------------------------------------------------------------------------------------\033[0m|\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|____________________________________________________________________________________________________________________|\n");
}

void client_start(char *name)
{
	printf("\033[1;1H\033[J");
	printf("______________________________________________________________________________________________________________________\n");
	printf("|  ___________                                                                                                       |\n");
	printf("|  | 每日心情| 功能服务：| help 重置 | chat 私聊 | all 群聊  | see  查看在线用户| data 查看历史记录 | change 改名    |\n");
	printf("|  |         |           | exit 退出 | face 表情 | hi  常用语| trans 发送文件   | password 修改密码 |                |\n");
	printf("|  | ( =_= ) |                                                                                                       |\n");
	printf("|  |_________| \033[44m普通用户 %s\033[0m\n", name);
	printf("|\033[32m--------------------------------------------------------------------------------------------------------------------\033[0m|\n");
	printf("|                                                                                                   |  \033[42m当前在线用户\033[0m  |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|                                                                                                   |                |\n");
	printf("|\033[32m--------------------------------------------------------------------------------------------------------------------\033[0m|\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|                                                                                                                    |\n");
	printf("|____________________________________________________________________________________________________________________|\n");
}
