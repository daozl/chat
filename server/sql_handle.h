#ifndef __SQL_HANDLE__
#define __SQL_HANDLE__

void Check_Sql(int rc, sqlite3 *db);
void Open_Sql(sqlite3 **db);
void Create_User_Sql(sqlite3 *db);
void Create_Data_Sql(sqlite3 *db);
void Create_Online_Sql(sqlite3 *db);
void Create_Server_Sql(sqlite3 *db);
void Reg_Sql(sqlite3 *db, char *name, char *password);
void Log_Sql(sqlite3 *db, char *name, int sockfd);
void Delete_Online_Sql(sqlite3 *db, int sockfd);
int Inquire_User_Sql(sqlite3 *db, char *user);
int Inquire_Id_Sql(sqlite3 *db, char *user);
int Inquire_Password_Sql(sqlite3 *db, char *user, char *password);
int Inquire_Online_Sql(sqlite3 *db, char *user);
void Insert_Server_Sql(sqlite3 *db, char *time);
void Insert_Data_Sql(sqlite3 *db, struct chat *temp);
int Inquire_Online_Fd_Sql(sqlite3 *db, char *user);
int Inquire_Online_Flag_Sql(sqlite3 *db, char *user);
int Update_Flag_Sql(sqlite3 *db, char *name, int flag);
int Update_Password_Sql(sqlite3 *db, char *name, char *password);
int Update_User_Sql(sqlite3 *db, char *name, char *toname);
int Update_Data_Sql(sqlite3 *db, char *name, char *toname);
int Delete_User_Sql(sqlite3 *db, char *name);
void See_Online_All_Sql(sqlite3 *db, struct chat *temp);
void Send_Online_All_Sql(sqlite3 *db, struct chat *temp);
void Send_Data_Sql(sqlite3 *db, struct chat *temp);

#endif
