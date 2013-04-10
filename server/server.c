#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../common/common.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
pthread_t thread_list[100];
int thread_list_id[100];
int num_thread=0;
char buffer[256];
void *thread_function(void *arg);
int init();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
		int sockfd,portno,clilen;
		struct sockaddr_in serv_addr,cli_addr;
		int* csock;
		int rc;
		if (argc < 2){
				fprintf(stderr,"ERROR, no port provided");
				exit(1);
		}
		
		sockfd = socket(AF_INET,SOCK_STREAM,0);
		if (sockfd < 0){
			printf("ERROR opening socket");
			exit(1);
		}
		bzero((char *)&serv_addr,sizeof(serv_addr));
		
		portno = atoi(argv[1]);
		
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(portno);
		
		rc =  bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if (rc == -1) {
			fprintf(stderr, "unable to bind to socket\n");
			exit(1);
		}
		
		listen(sockfd,5);
		printf("waiting for client...\n");
		while (1){
			clilen = sizeof(cli_addr);
			csock = (int*)malloc(sizeof(int));
			if((*csock = accept( sockfd, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen))!= -1){
				 printf("---------------------\nReceived connection from %s\n",inet_ntoa(cli_addr.sin_addr));
				 thread_list_id[num_thread] = pthread_create( &(thread_list[num_thread]), 0, &thread_function, (void *)csock );
				 pthread_detach(thread_list[num_thread]);
			 }
			 else{
				 fprintf(stderr, "Error accepting %d\n", errno);
			 }
			num_thread ++;
		}
		return 0;			
}


void *thread_function(void *arg){
	int rc;
	int sockid;
	int *csock = (int*)arg;
	sockid = *csock;
	/*
	//Reading command
	while (1){
		bzero(buffer,255);
		#ifdef DEBUG
			printf("from sockid %d \n",sockid);
		#endif
		rc = read(sockid,buffer,255);
		if (rc < 0){
			printf("error");
		}
		if (rc == 0){
			break;
		}
		printf("command: %s \n",buffer);
		
	}
	*/
	char buffer[150];
	FILE* fp = fopen("test.jpg","wb");    // buffer contains the name sent by client: "server.txt"
   	
        while(1){
               // bzero(buffer,150);
                recv(sockid,buffer,150,0);
                if(strcmp(buffer,"quit")==0)
                {
                	break;  
                }
                
                fwrite(buffer,1,150,fp);
        }
        fclose(fp);
	
	close(sockid);
	
	return NULL;
}
