#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define BUF_SIZE 1025

void send_message(int sockid,const char* command){};
void send_file(int sock,const char* filename){};
void recv_file(int sockfd,const char* filename);
int round_to_even ( float f );
