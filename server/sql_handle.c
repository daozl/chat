#include "head.h"
#include "sql_handle.h"

void Check_Sql(int rc, sqlite3 *db)
{
	if (rc != SQLITE_OK)
	{
		printf("SQL error : %s %d\n", sqlite3_errmsg(db), __LINE__);
		exit(1);
	}
}

void Open_Sql(sqlite3 **db)
{
	int rc;

	rc = sqlite3_open("./server.db", db);
	Check_Sql(rc, *db);
}

void Create_User_Sql(sqlite3 *db)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "create table user(id integer primary key autoincrement,name text,password text)");
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
}

void Create_Data_Sql(sqlite3 *db)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "create table data(id integer primary key autoincrement,time text,name text,toname text,msg text)");
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
}

void Create_Online_Sql(sqlite3 *db)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "create table online(id integer primary key autoincrement,name text,socket integer,flag integer)");
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
}

void Create_Server_Sql(sqlite3 *db)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "create table server(id integer primary key autoincrement,time text)");
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
}

void Reg_Sql(sqlite3 *db, char *name, char *password)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "insert into user(name,password) values('%s','%s')", name, password);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	Check_Sql(rc, db);
}

void Log_Sql(sqlite3 *db, char *name, int sockfd)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "insert into online(name,socket,flag) values('%s',%d,1)", name, sockfd);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	Check_Sql(rc, db);
}

void Delete_Online_Sql(sqlite3 *db, int sockfd)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "delete from online where socket=%d", sockfd);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	Check_Sql(rc, db);
}

int Inquire_User_Sql(sqlite3 *db, char *user)
{
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from user", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		if (0 == userflag)
		{
			return USERIN;
		}
		rc = sqlite3_step(stmt);
	}
	return USEROUT;
}

int Inquire_Id_Sql(sqlite3 *db, char *user)
{
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from user", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		if (0 == userflag)
		{
			return atoi(sqlite3_column_text(stmt, 0));
		}
		rc = sqlite3_step(stmt);
	}
	return USEROUT;
}

int Inquire_Password_Sql(sqlite3 *db, char *user, char *password)
{
	int rc;
	int userflag = 1;
	int passwordflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from user", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		passwordflag = strcmp(password, sqlite3_column_text(stmt, 2));
		if (0 == userflag && 0 == passwordflag)
		{
			return PASSWORDOK;
		}
		rc = sqlite3_step(stmt);
	}
	return PASSWORDNO;
}

int Inquire_Online_Sql(sqlite3 *db, char *user)
{
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from online", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		if (0 == userflag)
		{
			return ONLINEIN;
		}
		rc = sqlite3_step(stmt);
	}
	return ONLINEOUT;
}

void Insert_Server_Sql(sqlite3 *db, char *time)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "insert into server(time) values('%s')", time);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	Check_Sql(rc, db);
}

void Insert_Data_Sql(sqlite3 *db, struct chat *temp)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "insert into data(time,name,toname,msg) values('%s','%s','%s','%s')",
			    temp->time, temp->name, temp->toname, temp->msg);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	Check_Sql(rc, db);
}

int Inquire_Online_Fd_Sql(sqlite3 *db, char *user)
{
	char fd[MAX];
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from online", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		if (0 == userflag)
		{
			strcpy(fd, sqlite3_column_text(stmt, 2));
			return atoi(fd);
		}
		rc = sqlite3_step(stmt);
	}
	return ONLINEOUT;
}

int Inquire_Online_Flag_Sql(sqlite3 *db, char *user)
{
	char flag[MAX];
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from online", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		userflag = strcmp(user, sqlite3_column_text(stmt, 1));
		if (0 == userflag)
		{
			strcpy(flag, sqlite3_column_text(stmt,3));
			return atoi(flag);
		}
		rc = sqlite3_step(stmt);
	}
	return -99;
}

int Update_Flag_Sql(sqlite3 *db, char *name, int flag)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "update online set flag = %d where name = '%s'", flag, name);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (SQLITE_OK == rc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Update_Password_Sql(sqlite3 *db, char *name, char *password)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "update user set password = '%s' where name = '%s'", password, name);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (SQLITE_OK == rc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Update_User_Sql(sqlite3 *db, char *name, char *toname)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "update user set name = '%s' where name = '%s'", toname, name);
	rc= sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (SQLITE_OK == rc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Update_Data_Sql(sqlite3 *db, char *name, char *toname)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "update data set name = '%s' where name = '%s'", toname, name);
	rc= sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (SQLITE_OK == rc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Delete_User_Sql(sqlite3 *db, char *name)
{
	char sql[MAX];
	int rc;

	sprintf(sql, "delete from user where name = '%s'", name);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (SQLITE_OK == rc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Send_Online_All_Sql(sqlite3 *db, struct chat *temp)
{
	char fd[MAX];
	int rc;
	int flag;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from online", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		flag = strcmp(temp->name, sqlite3_column_text(stmt, 1));
		strcpy(fd, sqlite3_column_text(stmt, 2));
		if (flag != 0)
		{
			write(atoi(fd), temp, sizeof(struct chat));
		}
		rc = sqlite3_step(stmt);
	}
}

void See_Online_All_Sql(sqlite3 *db, struct chat *temp)
{
	int rc;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from online", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		strcpy(temp->msg, sqlite3_column_text(stmt, 1));
		write(temp->sockfd, temp, sizeof(struct chat));
		sleep(1);
		rc = sqlite3_step(stmt);
	}
}

void Send_Data_Sql(sqlite3 *db, struct chat *temp)
{
	char name[MAX];
	char toname[MAX];
	int rc;
	int userflag = 1;
	sqlite3_stmt *stmt = NULL;

	rc = sqlite3_prepare_v2(db, "select * from data", -1, &stmt, 0);
	Check_Sql(rc, db);
	rc = sqlite3_step(stmt);
	while (SQLITE_ROW == rc)
	{
		strcpy(name, sqlite3_column_text(stmt, 2));
		strcpy(toname, sqlite3_column_text(stmt, 3));
		if (0 == strcmp(temp->name, name))
		{
			strcat(temp->msg, "你");
			strcat(temp->msg, "对 ");
			strcat(temp->msg, toname);
			strcat(temp->msg, " 说：");
			strcat(temp->msg, sqlite3_column_text(stmt, 4));
			strcpy(temp->time, sqlite3_column_text(stmt, 1));
			write(temp->sockfd, temp, sizeof(struct chat));
			memset(temp->msg, 0, sizeof(temp->msg));
		}
		if (0 == strcmp(temp->name, toname))
		{
			strcat(temp->msg, toname);
			strcat(temp->msg, " 对你说：");
			strcat(temp->msg, sqlite3_column_text(stmt, 4));
			strcpy(temp->time, sqlite3_column_text(stmt, 1));
			write(temp->sockfd, temp, sizeof(struct chat));
			memset(temp->msg, 0, sizeof(temp->msg));
		}
		rc = sqlite3_step(stmt);
	}
}

