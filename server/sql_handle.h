#ifndef SQL_HANDLE_H__
#define SQL_HANDLE_H__

void check_sql(int rc,sqlite3 *db);
void open_sql(sqlite3 **db);
void create_user_sql(sqlite3 *db);
void create_data_sql(sqlite3 *db);
void create_online_sql(sqlite3 *db);
void create_server_sql(sqlite3 *db);
void reg_sql(sqlite3 *db,char *name,char *password);
void log_sql(sqlite3 *db,char *name,int sockfd);
void delete_online_sql(sqlite3 *db,int sockfd);
int inquire_user_sql(sqlite3 *db,char *user);
int inquire_id_sql(sqlite3 *db,char *user);
int inquire_password_sql(sqlite3 *db,char *user,char *password);
int inquire_online_sql(sqlite3 *db,char *user);
void insert_server_sql(sqlite3 *db,char *time);
void insert_data_sql(sqlite3 *db,struct chat *temp);
int inquire_online_fd_sql(sqlite3 *db, char *user);
int inquire_online_flag_sql(sqlite3 *db,char *user);
int update_flag_sql(sqlite3 *db,char *name, int flag);
int update_password_sql(sqlite3 *db,char *name,char *password);
int update_user_sql(sqlite3 *db,char *name,char toname);
int update_data_sql(sqlite3 *db,char *name,char toname);
int delete_user_sql(sqlite3 *db,char *name);
void see_online_all_sql(sqlite3 *db,struct chat *temp);
void send_online_all_sql(sqlite3 *db,struct chat *temp);
void send_data_sql(sqlite3 *db,struct chat *temp);

#endif
