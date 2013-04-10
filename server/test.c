
/*

Server portion of sendfile example.

usage: server [port]

Copyright (C) 2003 Jeff Tranter.


This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define MAX_THREADS 10
 
void *thread_function(void *);
 
int sockfd, new_fd[MAX_THREADS],  res, times=0, i, num=0, *p_num;
socklen_t sin_size;
struct sockaddr_in my_addr;
struct sockaddr_in their_addr;
struct stat filestat;
pthread_t accept_thread[MAX_THREADS];
void *thread_result;
void send_file(int sock) 
{ 
    char buf[1025]; 
    const char* filename = "testfile"; 
    FILE *file = fopen(filename, "rb"); 
    if (!file)
    {
        printf("Can't open file for reading"); 
        return;
    }
    while (!feof(file)) 
    { 
        int rval = fread(buf, 1, sizeof(buf), file); 
        if (rval < 1)
        {
            printf("Can't read from file");
            fclose(file);
            return;
        }

        int off = 0;
        do
        {
            int sent = send(sock, &buf[off], rval - off, 0);
            if (sent < 1)
            {
                // if the socket is non-blocking, then check
                // the socket error for WSAEWOULDBLOCK/EAGAIN
                // (depending on platform) and if true then
                // use select() to wait for a small period of
                // time to see if the socket becomes writable
                // again before failing the transfer...

                printf("Can't write to socket");
                fclose(file);
                return;
            }

            off += sent;
        }
        while (off < rval);
    } 

    fclose(file);
} 

void *thread_function(void *arg){
	int numbytes=0, th_num=0, *p_th_num;
	char buf[1000000];
	char filename[100];
	int rc;
	p_th_num = (int *)arg;
	th_num = *p_th_num;
	/* get the file name from the client */
    rc = recv(th_num, filename, sizeof(filename), 0);
    if (rc == -1) {
      fprintf(stderr, "recv failed: %s\n", strerror(errno));
      exit(1);
    }
	printf("filename %s",filename);
	close(th_num);
	return NULL;
}

int main(int argc, char **argv)
{
	
  int port = 1234;           /* port number to use */
  int sock;                  /* socket desciptor */
  int desc;                  /* file descriptor for socket */
  int fd;                    /* file descriptor for file to send */
  struct sockaddr_in addr;   /* socket parameters for bind */
  struct sockaddr_in addr1;  /* socket parameters for accept */
  int    addrlen;            /* argument to accept */
  struct stat stat_buf;      /* argument to fstat */
  off_t offset = 0;          /* file offset */
  char filename[100];   /* filename to send */
  int rc;                    /* holds return code of system calls */

  /* check command line arguments, handling an optional port number */
  if (argc == 2) {
    port = atoi(argv[1]);
    if (port <= 0) {
      fprintf(stderr, "invalid port: %s\n", argv[1]);
      exit(1);
    }
  } else if (argc != 1) {
    fprintf(stderr, "usage: %s [port]\n", argv[0]);
    exit(1);
  }
	
  /* create Internet domain socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    fprintf(stderr, "unable to create socket: %s\n", strerror(errno));
    exit(1);
  }

  /* fill in socket structure */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  /* bind socket to the port */
  rc =  bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  if (rc == -1) {
    fprintf(stderr, "unable to bind to socket: %s\n", strerror(errno));
    exit(1);
  }

  /* listen for clients on the socket */
  rc = listen(sock, 1);
  if (rc == -1) {
    fprintf(stderr, "listen failed: %s\n", strerror(errno));
    exit(1);
	  }
  while (1) {

    /* wait for a client to connect */

	if(new_fd[num] = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size) == -1)
	{
			perror("accept");
			exit(1);
		}
	
	res = pthread_create( &(accept_thread[times]), NULL, thread_function, (void *)new_fd[num]  );
	if (res != 0){
		perror("Thread create failed!\n");
		exit(EXIT_FAILURE);
	}
	num++;
	times++;
    

    ///* null terminate and strip any \r and \n from filename */
		//filename[rc] = '\0';
    //if (filename[strlen(filename)-1] == '\n')
      //filename[strlen(filename)-1] = '\0';
    //if (filename[strlen(filename)-1] == '\r')
      //filename[strlen(filename)-1] = '\0';

    ///* exit server if filename is "quit" */
    //if (strcmp(filename, "quit") == 0) {
      //fprintf(stderr, "quit command received, shutting down server\n");
      //break;
    //}

    //fprintf(stderr, "received request to send file %s\n", filename);
    //send_file(desc);

    /* close socket descriptor */
    //close(desc);
  }

  /* close socket */
  close(sock);
  return 0;
}
