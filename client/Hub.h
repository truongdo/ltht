#include <pthread.h>
#include <stdio.h>
#include "Directory.h"
#include <vector>
#include "Network.h"
using namespace std;
#define red   "\033[0;31m"        /* 0 -> normal ;  31 -> red */
#define cyan  "\033[1;36m"        /* 1 -> bold ;  36 -> cyan */
#define green "\033[4;32m"        /* 4 -> underline ;  32 -> green */
#define blue  "\033[9;34m"        /* 9 -> strike ;  34 -> blue */
#define blueDir  "\033[1;34m"        /* 9 -> strike ;  34 -> blue */

#define black  "\033[0;30m"
#define brown  "\033[0;33m"
#define magenta  "\033[0;35m"
#define gray  "\033[0;37m"
 
#define none   "\033[0m"        /* to flush the previous property */


class Hub{
		int sockfd;	//use to send and receive command and text
		//int sockfd_binary;	//use to receiving data (for and upload file)
		int mainThreadID;
		Directory dir;
		Directory pDir; // parent directory
		pthread_t mainThread;
		
		public:
			Network net = Network();
			void init_network();
			void initRootDir();
			void UpdateDirContent();
			void saveSession();
			void loadSession();
			void run();
			void showDirContent();
			void goForward(char* dirname);
			void goBackward();
			static void *thread_getInput(void *arg);
};
