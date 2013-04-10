#include <iostream>
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
#include <stdlib.h>
#include <stdio.h>
#include <sys/un.h>
class Network{
		char host[100];
		int port;
		int sockfd;
		int restoreLastSession();
		public:
				void init_network();
				int sendFile(char *filename);
				void GetConnect();
				int sendFileName(char *filename);
};
