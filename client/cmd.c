#include "head.h"
#include "cmd.h"

int analy_start_cmd(char *cmd)
{
	if(strcmp(cmd,"reg") == 0){
		return REG;
	}
	else if(strcmp(cmd,"log") == 0){
		return LOG;
	}
	else if(strcmp(cmd,"help") == 0){
		return USERHELP;
	}
	else if(strcmp(cmd,"exit") == 0){
		return USEREXIT;
	}
	else{
		return ERROR;
	}
}

int analy_admin_cmd(char *cmd)
{	
	if(strcmp(cmd,"chat") == 0){
		return CHAT;
	}
	else if(strcmp(cmd,"all") == 0){
		return ALL;
	}
	else if(strcmp(cmd,"see") == 0){
		return SEE;
	}
	else if(strcmp(cmd,"data") == 0){
		return DATA;
	}
	else if(strcmp(cmd,"face") == 0){
		return FACE;
	}
	else if(strcmp(cmd,"hi") == 0){
		return HI;
	}
	else if(strcmp(cmd,"trans") == 0){
		return TRANS;
	}
	else if(strcmp(cmd,"password") == 0){
		return PASSWORD;
	}
	else if(strcmp(cmd,"help") == 0){
		return HELP;
	}
	else if(strcmp(cmd,"exit") == 0){
		return EXIT;
	}
	else{
		return ERROR;
	}
}

int analy_client_cmd(char *cmd)
{
	if(strcmp(cmd,"chat") == 0){
		return CHAT;
	}
	else if(strcmp(cmd,"all") == 0){
		return ALL;
	}
	else if(strcmp(cmd,"see") == 0){
		return SEE;
	}
	else if(strcmp(cmd,"data") == 0){
		return DATA;
	}
	else if(strcmp(cmd,"face") == 0){
		return FACE;
	}
	else if(strcmp(cmd,"hi") == 0){
		return HI;
	}
	else if(strcmp(cmd,"trans") == 0){
		return TRANS;
	}
	else if(strcmp(cmd,"password") == 0){
		return PASSWORD;
	}
	else if(strcmp(cmd,"help") == 0){
		return HELP;
	}
	else if(strcmp(cmd,"exit") == 0){
		return EXIT;
	}
	else{
		return ERROR;
	}
}
