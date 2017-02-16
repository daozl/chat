#include "head.h"
#include "sql_handle.h"
#include "cmd.h"
#include "start.h"

int main()
{
	int sockfd;
	int accfd;
	int clifd;
	int maxfd;
	int nready;
	struct chat temp;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int client[FD_SETSIZE];
	int maxi;
	fd_set rset;
	fd_set allset;
	int addr_len;
	int i;
	int n;
	char addr_ip[20];
	time_t timep;
	char tm[128];
	sqlite3 *db = NULL;
	int option = 1;

	Open_Sql(&db);
	Create_User_Sql(db);
	Create_Data_Sql(db);
	Create_Online_Sql(db);
	Create_Server_Sql(db);
	time(&timep);
	strcpy(tm, ctime(&timep));
	tm[strlen(tm) - 1] = '\0';
	Insert_Server_Sql(db, tm);
	Start_Server();

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket failure!\n");
		exit(1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
	{
		printf("setsockopt failure!\n");
		exit(1);
	}
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("bind failure!\n");
		exit(1);
	}
	if (listen(sockfd, 10) < 0)
	{
		printf("listen failure!\n");
		exit(1);
	}
	printf("----->服务器正在等待客户端连接.....\n");

	maxfd = sockfd;
	maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);
	while (1)
	{
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(sockfd, &rset))
		{
			addr_len = sizeof(struct sockaddr_in);
			if ((accfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0)
			{
				printf("accept failure!\n");
				exit(1);
			}
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i] < 0)
				{
					client[i] = accfd;
					break;
				}
			}
			if (FD_SETSIZE == i)
			{
				printf("Full clients!\n");
				exit(1);
			}
			FD_SET(accfd, &allset);
			if (accfd > maxfd)
			{
				maxfd = accfd;
			}
			if (i > maxi)
			{
				maxi = i;
			}
			if (--nready <= 0)
			{
				continue;
			}
		}

		for (i = 0; i < FD_SETSIZE; i++)
		{
			if ((clifd = client[i]) < 0)
			{
				continue;
			}
			if (FD_ISSET(clifd, &rset))
			{
				printf("客户端clifd = %d 已经成功连接...\n", clifd);
				n = read(clifd, &temp, sizeof(struct chat));
				if (0 == n)
				{
					printf("客户端clifd = %d 已经离开本服务器...\n", clifd);
					Delete_Online_Sql(db, clifd);
					fflush(stdout);
					close(clifd);
					FD_CLR(clifd, &allset);
					client[i] = -1;
				}
				else
				{
					temp.sockfd = clifd;
					inet_ntop(AF_INET, &client_addr.sin_addr, addr_ip, sizeof(addr_ip));
					addr_ip[strlen(addr_ip)] = '\0';
					printf("客户端ip = %s , 端口port = %d\n", addr_ip, ntohs(client_addr.sin_port));
					temp.revert = Cmd_User(db, &temp, clifd);
					printf("开始向客户端发送命令...\n");
					if (REGOK == temp.revert || REGNO == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (1 == temp.revert || 0 == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (PASSWORDOK == temp.revert || PASSWORDNO == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (USERIN == temp.revert || USEROUT == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (ONLINEIN == temp.revert || ONLINEOUT == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (MYFLAGOK == temp.revert || MYFLAGNO == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (TOFLAGOK == temp.revert || TOFLAGNO == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (TRANSOK == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (KICKOK == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (CHATOK == temp.revert)
					{
						write(temp.sockfd, &temp, sizeof(struct chat));
					}
					else if (DATAOK == temp.revert)
					{
						Send_Data_Sql(db, &temp);
					}
					else if (ALLOK == temp.revert)
					{
						Send_Online_All_Sql(db, &temp);
					}
					else if (SEEOK == temp.revert)
					{
						See_Online_All_Sql(db, &temp);
					}
					printf("发送完毕！\n");
					memset(&temp, 0, sizeof(struct chat));
				//	if (1 == n)
				//	{
				//		exit(1);
				//	}
				}
				if (--nready <= 0)
				{
					break;
				}
			}
		}
	}
	close(sockfd);
	return 0;
}
