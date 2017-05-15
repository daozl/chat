#include "head.h"
#include "thread.h"

void *thread_read(void *arg)
{
	int fd = *((int *)arg);
	struct chat temp;

	while (1)
	{
		check_screen();
		read(fd, &temp, sizeof(struct chat));
		switch (temp.cmd)
		{
			case CHAT:
				{
					if (ONLINEOUT == temp.revert)
					{
						printf("\033[%d;2H您需要呼叫的用户已经下线！\n", row++);
					}
					else if (CHATOK == temp.revert)
					{
						printf("\033[%d;2H(%s)   %s 对你说： %s\n", row++, temp.time, temp.name, temp.msg);
					}
					else
					{
						printf("%d", temp.revert); //
						printf("\033[%d;2H接受到错误的服务器消息！\n", row++);
					}
					printf("\033[24;2H");
					fflush(stdout);
					break;
				}

			case ALL:
				{
					if (ALLOK == temp.revert)
					{
						printf("\033[%d;2H(%s)   %s 对 所有人 说： %s\n",row++, temp.time, temp.name, temp.msg);
					}
					else
					{
						printf("\033[%d;2H接受到错误的服务器消息！\n", row++);
					}
					printf("\033[24;2H");
					fflush(stdout);
					break;
				}

			case SEE:
				{
					printf("\033[%d;105H %s", nsee++, temp.msg);
					fflush(stdout);
					break;
				}

			case DATA:
				{
					printf(" (%s)   %s\n", temp.time, temp.msg);
					break;
				}

			case TRANS:
				{
					if (ONLINEOUT == temp.revert)
					{
						printf("\033[%d;2H您需要呼叫的用户已经下线！\n", row++);
					}
					else if (TRANSOK == temp.revert)
					{
						int num;
						int file;
						char data[MAX];

						printf("\033[%d;2H(%s)   %s 向您发送文件(%s)\n", row++, temp.time, temp.name, temp.filename);
						sprintf(data, "./temp/%s", temp.filename);
						file = open(data, O_CREAT | O_RDWR | O_NONBLOCK, 0777);
						if (-1 == file)
						{
							printf("\033[%d;2H文件打开失败！\n", row++);
						}
						else
						{
							lseek(file, 0, SEEK_SET);
							num = write(file, temp.msg, strlen(temp.msg));
							if (-1 == num)
							{
								printf("\033[%d;2H文件写入失败！\n", row++);
							}
							else
							{
								printf("\033[%d;2H文件接受成功！请在./temp目录下查看！\n", row++);
							}
						}
						close(file);
					}
					else
					{	
						printf("\033[%d;2H接受到错误的服务器消息！\n", row++);
					}
					printf("\033[24;2H");
					fflush(stdout);
					break;
				}

			case PASSWORD:
				{
					if (1 == temp.revert)
					{
						printf("\033[%d;2H修改密码成功！系统即将自动退出！请重新登录！\n", row++);
						sleep(1);
						system("reset");
						exit(0);
					}
					else if (0 == temp.revert)
					{
						printf("\033[%d;2H修改密码失败！\n", row++);
					}
					else
					{
						printf("\033[%d;2H收到错误的服务器消息！\n", row++);
					}
					break;
				}
		}
		memset(&temp, 0, sizeof(struct chat));
	}
}
