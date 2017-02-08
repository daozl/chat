#include "head.h"
#include "cmd.h"

int cmd_user(sqlite3 *db,struct chat *temp,int sockfd)
{
	int flag;
	int sayflag;
	printf("cmd = %d\n",temp->cmd);
	switch (temp->cmd)
	{
		case REG:
			flag = inquire_user_sql(db,temp->name);
			if(flag == USERIN){
				return REGNO;
			}
			else{
				reg_sql(db,temp->name,temp->password);
				temp->flag = inquire_id_sql(db,temp->name);
				return REGOK;
			}
			break;
		case LOG:
			{
				int flagpassword;
				flag = inquire_online_sql(db,temp->name);
				if(ONLINEIN == flag){
					return ONLINEIN;
				}
				else{
					flagpassword = inquire_password_sql(db,temp->name,temp->password);
					if(PASSWORDOK == flagpassword){
						log_sql(db,temp->name,sockfd);
						return PASSWORDOK;
					}
					else{
						return PASSWORDNO;
					}
				}
				break;
			}
		case CHAT:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					return ONLINEOUT;
				}
				else{
					sayflag = inquire_online_flag_sql(db,temp->name);
					if(sayflag == 0){
						return MYFLAGNO;
					}
					else{
						temp->flag = flag;
						temp->sockfd = tempfd;
						insert_data_sql(db,temp);
						return CHATOK;
					}
				}
				break;
			}
		case ALL:
			sayflag = inquire_online_flag_sql(db,temp->name);
			if(sayflag == 0){
				return MYFLAGNO;
			}
			else{
				insert_data_sql(db,temp);
				return ALLOK;
			}
			break;
		case PASSWORD:
			flag = update_password_sql(db,temp->name,temp->password);
			return flag;
			break;
		case KICK:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					return ONLINEOUT;
				}
				else{
					temp->sockfd = tempfd;
				}
				break;
			}
		case SHUT:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					return ONLINEOUT;
				}
				else{
					flag = update_flag_sql(db,temp->toname);
					if(flag == 1){
						temp->sockfd = tempfd;
					}
					return flag;
				}
				break;
			}
		case REMOVE:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					return ONLINEOUT;
				}
				else{
					sayflag = inquire_online_flag_sql(db,temp->toname);
					if(sayflag == 1){
						return TOFLAGOK;
					}
					else{
						flag = update_flag_sql(db,temp->toname,1);
						if(flag == 1){
							temp->sockfd = tempfd;
						}
						return flag;
					}
				}
				break;
			}
		case CANCEL:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					flag = delete_user_sql(db,temp->toname);
					return flag;
				}	
				else{
					return ONLINEIN;
				}
				break;
			}
		case SEE:
				return SEEOK;
				break;
		case DATA:
			return DATAOK;
		case TRANS:
			{
				int tempfd;
				tempfd = inquire_online_fd_sql(db,temp->toname);
				if(ONLINEOUT == tempfd){
					return ONLINEOUT;
				}
				else{
					temp->sockfd = tempfd;
					return TRANSOK;
				}
			}
		case CHANGE:
			{
				flag = inquire_user_sql(db,temp->toname);
				if(USERIN == flag){
					return REGNO;
				}
				else{
					flag = update_user_sql(db,temp->name,temp->toname);
					if(flag == 1){
						return update_data_sql(db,temp->name,temp->name);
					}
					else{
						return 0;
					}
				}
				break;
			}
	}
}
