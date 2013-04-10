#include "Network.h"
int Network::restoreLastSession(){
		FILE *f = fopen("session","r");
		if (f == NULL){
				return 0;
		}else{
				try{
					fgets(host,100,f);
					char p[5];
					fgets(p,5,f);
					port = atoi(p);
				}catch(const char *str){
						return 0;
				}
		}
		return 1;
}
void Network::init_network(){
		int rc = restoreLastSession();
		if (rc == 0){
				std::cout << "Fail to restore last session "<<std::endl;
				std::cout << "Please input manualy \n";
				std::cout << "Enter Hostname: "<<std::endl;
				std::cin >> host;
				std::cout << "Enter Port: "<<std::endl;
				std::cin >> port;
				
		}
				
}
int Network::sendFile(char *filename){
	FILE* fp = fopen(filename,"rb");      // buffer = "server.txt"
	char buffer[150];
	printf("uploading...\n");
   	while(!feof(fp)){
    		bzero(buffer,150);
   			fread(buffer,sizeof(char),150,fp);
   			int n = send(sockfd,buffer,150,0);
   			if (n < 0) 
       				perror("ERROR writing to socket");
   	}		
   		write(sockfd,"quit",150);     
   		fclose(fp);
}
int Network::sendFileName(char *filename){
   	write(sockfd,filename,150);     
}
void Network::GetConnect(){
	
	struct sockaddr_in address;
	//TCP socket
	std::cout << "Connecting to "<<host<<":"<<port <<std::endl;
	if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) == -1 ){
		perror("socket");
		exit(1);
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(host);
	bzero( &(address.sin_zero), 8 );
	//Connect to server
	if ( connect(sockfd, (struct sockaddr*)&address, sizeof(struct sockaddr)) == -1){
		perror("connect");
	}
//	return sockfd;
}
