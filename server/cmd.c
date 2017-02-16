#include "head.h"
#include "cmd.h"

int Cmd_User(sqlite3 *db, struct chat *temp, int sockfd)
{
	int flag;
	int sayflag;
	printf("cmd = %d\n", temp->cmd);
	switch (temp->cmd)
	{
		case REG:
			{
				flag = Inquire_User_Sql(db, temp->name);
				if (USERIN == flag)
				{
					return REGNO;
				}
				else
				{
					Reg_Sql(db, temp->name, temp->password);
					temp->flag = Inquire_Id_Sql(db, temp->name);
					return REGOK;
				}
				break;
			}

		case LOG:
			{
				int flagpassword;
				flag = Inquire_Online_Sql(db, temp->name);
				if (ONLINEIN == flag)
				{
					return ONLINEIN;
				}
				else
				{
					flagpassword = Inquire_Password_Sql(db, temp->name, temp->password);
					if (PASSWORDOK == flagpassword)
					{
						Log_Sql(db, temp->name, sockfd);
						return PASSWORDOK;
					}
					else
					{
						return PASSWORDNO;
					}
				}
				break;
			}

		case CHAT:
			{
				int tempfd;
				tempfd = Inquire_Online_Fd_Sql(db, temp->toname);
				if (ONLINEOUT == tempfd)
				{
					return ONLINEOUT;
				}
				else
				{
					sayflag = Inquire_Online_Flag_Sql(db, temp->name);
					if (0 == sayflag)
					{
						return MYFLAGNO;
					}
					else
					{
						temp->flag = flag; 
						temp->sockfd = tempfd;
						Insert_Data_Sql(db, temp);
						return CHATOK;
					}
				}
				break;
			}

		case ALL:
			{
				sayflag = Inquire_Online_Flag_Sql(db, temp->name);
				if (0 == sayflag)
				{
					return MYFLAGNO;
				}
				else
				{
					Insert_Data_Sql(db, temp);
					return ALLOK;
				}
				break;
			}

		case PASSWORD:
			{
				flag = Update_Password_Sql(db, temp->name, temp->password);
				return flag;
				break;
			}

		case KICK:
			{
				int tempfd;
				tempfd = Inquire_Online_Fd_Sql(db, temp->toname);
				if (ONLINEOUT == tempfd)
				{
					return ONLINEOUT;
				}
				else
				{
					temp->sockfd = tempfd;
					return KICKOK;
				}
				break;
			}

		case SHUT:
			{
				int tempfd;
				tempfd = Inquire_Online_Fd_Sql(db, temp->toname);
				if (ONLINEOUT == tempfd)
				{
					return ONLINEOUT;
				}
				else
				{
					flag = Update_Flag_Sql(db, temp->toname, 0);
					if (1 == flag)
					{
						temp->sockfd = tempfd;
					}
					return flag;
				}
				break;
			}

		case REMOVE:
			{
				int tempfd;
				tempfd = Inquire_Online_Fd_Sql(db,temp->toname);
				if (ONLINEOUT == tempfd)
				{
					return ONLINEOUT;
				}
				else
				{
					sayflag = Inquire_Online_Flag_Sql(db, temp->toname);
					if (1 == sayflag)
					{
						return TOFLAGOK;
					}
					else
					{
						flag = Update_Flag_Sql(db, temp->toname, 1);
						if (1 == flag)
						{
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
				tempfd = Inquire_Online_Fd_Sql(db, temp->toname);
				if (ONLINEOUT == tempfd)
				{
					flag = Delete_User_Sql(db, temp->toname);
					return flag;
				}
				else
				{
					return ONLINEIN;
				}
				break;
			}

		case SEE:
			{
				return SEEOK;
				break;
			}

		case DATA:
			{
				return DATAOK;
			}

		case TRANS:
			{
				int tempfd;
				tempfd = Inquire_Online_Fd_Sql(db, temp->toname);
				if (ONLINEOUT == tempfd)
				{
					return ONLINEOUT;
				}
				else
				{
					temp->sockfd = tempfd;
					return TRANSOK;
				}
			}

		case CHANGE:
			{
				flag = Inquire_User_Sql(db, temp->toname);
				if (USERIN == flag)
				{
					return REGNO;
				}
				else
				{
					flag = Update_User_Sql(db, temp->name, temp->toname);
					if (1 == flag)
					{
						return Update_Data_Sql(db, temp->name, temp->toname);
					}
					else
					{
						return 0;
					}
				}
				break;
			}
	}
}
