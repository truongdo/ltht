#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include "Hub.h"
#include "../common/common.h"
int sockfd, numbytes;

void handler (int sig){
	char *command = (char*)"client terminated";
	write(sockfd,command,strlen(command));
	exit(0);
}


int round_to_even ( float f )
{
   return (int)(f + 0.5f);
}
int main(int argc, char* argv[]){
	(void)signal(SIGINT,handler);
	Hub b = Hub();
	b.run();
	/*
	init_network();
	int sockfd;
	sockfd = GetConnect();
	Command cm = Command(sockfd);
	
	int rc;
	char command[10];
	while(1){
		printf("nhom5> ");
		scanf("%s",command);
		cm.handlerCommand(command);
	}
	*/
	//close(sockfd);
	return 0;
}
