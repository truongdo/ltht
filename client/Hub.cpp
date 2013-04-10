#include "Hub.h"
#include "string.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

void p(char* m){
	printf("%s$ ",m);
	}
void Hub::run(){
		//mainThread = pthread_create(&mainThread,0,&Hub::thread_getInput,0);
		Hub::net.init_network();
		Hub::net.GetConnect();
		char command[20];
		char *CD = "cd";
		char *RM = "rm";
		char *LS = "ls";
		char *UPLOAD = "upload";
		
		
		Hub::initRootDir();
		while(1){
				printf("<nhom5>:");
				//printf("%sHello%s, %sworld!\n", green, none, cyan);
				//printf("%s", none);
				p(Hub::dir.getName());
				scanf ("%[^\n]%*c", command);
				//check for cd command
				char *pupload = strstr(command, UPLOAD);
				char *pch = strstr(command, CD);
				
				if (pch){
						//Get dir name
						char *p = strtok(command, " ");
						char *dirname;
						while(p != NULL)
						{
							dirname=p;
							p=strtok(NULL," ");
						}
						if(strcmp("..",dirname) == 0){
								Hub::goBackward();
						}else{
							Hub::goForward(dirname);
						}
				}
				if (strcmp(command,LS) == 0){
						
						Hub::showDirContent();
				}
				
				if (pupload){
					//Get file name
						char *p = strtok(command, " ");
						char *filename;
						while(p != NULL)
						{
							filename=p;
							p=strtok(NULL," ");
						}
						printf("uploading %s",filename);
						Hub::net.sendFileName(filename);
						Hub::net.sendFile(filename);
					
				}
				
		}
		
}

void Hub::goForward(char* dirname){
	
		//Find dir with name
		int flag = 0;
		for(int i=0;i<Hub::dir.getCount();i++){
				if (strcmp(dirname,Hub::dir.getSubDir(i).getName()) == 0){
					Hub::pDir = Hub::dir;
					Hub::dir = dir.getSubDir(i);
					flag = 1;
					break;
				}
		}
		if (flag == 0){
				printf("bash: cd: fs: No such file or director\n");
		}
}
void Hub::goBackward(){
		int flag = 0;
		Hub::dir = Hub::pDir;
}
			
void Hub::showDirContent(){
		//update before show
		Hub::UpdateDirContent();
		for(int i=0;i<Hub::dir.getCount();i++){
				printf("%s%s%s\n",blueDir,Hub::dir.getSubDir(i).getName(),none);
		}
}
void Hub::UpdateDirContent(){
		//get directory list from server
		//then update to current directory
		//demo
		
		srand(time(NULL));
		int r = rand();
		
		vector<Directory> listDir(2);
		listDir[0].setName("Dir 1");
		listDir[0].setId(11);
		listDir[0].setPId(1);
		listDir[1].setName("Dir");
		listDir[1].setPId(1);
		Hub::dir.setDirList(listDir);
		
}

void Hub::initRootDir(){
		Hub::dir = Directory();
		Hub::dir.setName("home");
		Hub::dir.setId(1);
		Hub::pDir = Hub::dir;
		Hub::UpdateDirContent();
};
void* Hub::thread_getInput(void *arg){
		/*
		char command[20];
		while(1){
				scanf("%s",&command);
				printf("%s",command);
		}
		* */
}
