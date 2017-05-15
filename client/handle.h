#ifndef HANDLE_H__
#define HANDLE_H__

void wait_dian();
void my_fgets(char *buf,int bufsize, FILE *stream);
void check_screen();
void handle_see_board();
void reg(int sockfd, struct chat *temp);
void Log(int sockfd, struct chat *temp);
void chat_one(int sockfd, struct chat *temp);
void chat_all(int sockfd, struct chat *temp);
void see(int sockfd,struct chat *temp);
void data(int sockfd, struct chat *temp);
void password(int sockfd, struct chat *temp);
void trans(int sockfd, struct chat *temp);
void exit_tell(int sockfd, struct chat *temp);

#endif 
