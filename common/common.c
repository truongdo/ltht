#include "common.h"
#define BUF_SIZE 1025

void send_message(int sockid,const char* command){
	int ret;

	rc = write(sockid,command,strlen(command));	
	if (rc == -1){
		printf("Error: lost connection! (common.h)");
		exit(1);
	}

}
void send_file(int sock,const char* filename){
	char buf[BUF_SiZE];
	struct stat st;
	char size_file[20];
	
	FILE *file = fopen(filename,"rb");
//	stat(finame,&st);
	if (!file){
		printf("Can't open file %s for reading\n",filename);
		return;
	}
	while (!feof(file)){
		int rval = fread(buf,1,sizeof(buf),file);
		if (rval < 1){
			printf("Can't read from file\n");
			fclose(file);
			return;
		}

		int off = 0;
		do {
			int sent = send(sock,&buf[off],rval-off,0);
			if (sent < 1){
				printf("Can't write to socket");
				fclose(file);
				return;
			}
			off += sent;
		}while(off < rval);
	}
	fclose(file);
	
}
int round_to_even ( float f )
{
   return (int)(f + 0.5f);
}
void recv_file(int sockfd,const char* filename) 
{ 
    int rval; 
    char buf[1025]; 
    char buff_size[10];
    int size2read = sizeof(buf);
    int sizefile;
    int total = 0;
    FILE *file = fopen(filename, "wb"); 
    //sending filename to server
    send_command(filename);
    //get file info
    int intrc = read(sockfd,buff_size,sizeof(buff_size));
	if (intrc < 0){
			printf("error reading filesize");
			exit(1);
	}
	sizefile = atoi(buff_size);
	printf("sizefile %d\n",sizefile);
    if (!file)
    {
        printf("Can't open file for writing");
        return;
    }
    do
    {
        rval = recv(sockfd, buf, sizeof(buf), 0);
        total += rval;
        printf("total %d \n",round_to_even((float)total/sizefile));
        if (rval < 0)
        {
            printf("Can't read from socket");
            fclose(file);
            return;
        }
        if (rval == 0)
            break;
        int off = 0;
        do
        {
            int written = fwrite(&buf[off], 1, rval - off, file);
            if (written < 1)
            {
                printf("Can't write to file");
                fclose(file);
                return;
            }
            off += written;
        }
        while (off < rval);
    }while(rval == size2read);
printf("complete\n");
    fclose(file); 
} 
