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
	char add_ip[20];
	time_t timep;
	char tm[128];
	sqlite3 *db = NULL;
	int option = 1;

	open_sql(&db);
	create_user_sql(db);
	create_data_sql(db);
	create_online_sql(db);
	create_server_sql(db);
	time(&timep);
	strcpy(tm,ctime(&timep));
	tm[strlen(tm) - 1] = '\0';
	insert_server_sql(db,tm);
	start_server();

	if((sockfd = sockfd(AF_INET,SOCK_STREAM,0)) < 0){
		printf("socket failure!\n");
		exit(1);
	}
	if(setsockopt(sockfd,SQL_SOCKET,SO_REUSEADDR,&option,sizeof(option)) < 0){
		printf("setsockfd failure!\n");
		exit(1);
	}
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) < 0){
		printf("bind failure!\n");
		exit(1);
	}
	if(listen(sockfd,10) < 0){
		printf("listen failure!\n");
		exit(1);
	}
	printf("----->服务器正在等待客户连接.....\n");

	maxfd = sockfd;
	maxi = -1;
	for(i = 0; i < FD_SETSIZE;i++){
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(sockfd,&allset);
	while(1){
		rset = allset;
		nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&rset)){
			addr_len = sizeof(struct sockaddr_in);
			if((accfd = accept(sockfd,(struct sockaddr *)&client_addr,&addr_len)) < 0){
				printf("accept failure!\n");
				exit(1);
			}
			for(i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] < 0){
					client[i] = accfd;
					break;
				}
			}
			if(i == FD_SETSIZE){
				printf("Full client!\n");
				exit(1);
			}
			FD_SET(accfd,&allset);
			if(maxfd < accfd){
				maxfd = accfd;
			}
			if(max < i){
				maxi = i
			}
			if(--nready <= 0){
				continue;
			}
		}

		for(i = 0; i < FD_SETSIZE;i++){
			if((clifd = client[i]) < 0){
				continue;
			}
			if(FD_ISSET(clifd,&rset)){
				printf("客户端clifd = %d 已经连接...\n",clifd);
				n = read(clifd,&temp,sizeof(struct chat));
				if(n == 0){
					printf("客户端clifd = %d 已经离开本服务器");
					delete_online_sql(db,clifd);
					fflush(stdout);
					close(clifd);
					FD_CLR(clifd,&allset);
					client[i] = -1;
				}
				else{
					temp.sockfd = clifd;
					inet_ntop(AF_INDET,&client_addr.sin_addr,addr_ip,sizeof(addr_ip));
					addr_ip[strlen(addr_ip)] = '\0';
					printf("客户端ip = %s,端口port = %d\n",addr_ip,ntohs(client_addr.sin_port));
					temp.revert = cmd_user(db,&temp,clifd);
					printf("开始向客户端发送命令...\n");
					if(temp.revert == REGOK || temp.revert == REGNO){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == 1 || temp.revert == 0){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == PASSWORDOK || temp.revert == PASSWORDNO){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == USERIN || temp.revert == USEROUT){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == ONLINEIN || temp.revert == ONLINEOUT){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == MYFLAGOK || temp.revert == MYFLAGNO){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == TOFLAGOK || temp.revert == TOFALGNO){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == TRANSOK){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == KICKOK){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == CHATOK){
						write(temp.sockfd,&temp,sizeof(struct chat));
					}
					else if(temp.revert == DATAOK){
						send_data_sql(db,&temp);
					}
					else if(temp.revert == ALLOK){
						send_online_all_sql(db,&temp);
					}
					else if(temp.revert == SEEOK){
						see_online_all_sql(db,&temp);
					}
					printf("发送完毕！\n");
					memset(&temp,0,sizeof(struct chat));
				}
				if(--nready <= 0){
					break;
				}
			}
		}
	}
	close(sockfd);
	return 0;
}



























