
using namespace std;

class Command {
	char *command;
	int sockfd;
	public:
		Command(int s);
		void handlerCommand(char* command);
		void printCommands();
		int sendCommand(char *command);
};
Command::Command(int s){
		sockfd = s;
}
void Command::printCommands(){
	cout <<"Online file manager, version 1.0 - release 04/2013"<<endl;
	cout <<"Type `help name` to find out more about function `name`\n";
	cout << "Command lists: \n";
	cout << "ls		<>			show current directory\n";
	cout << "cd		<name dir>		go to <dir>\n";
}
int Command::sendCommand(char* command){
	int rc = write(sockfd,command,strlen(command));	
	return rc;
}
void Command::handlerCommand(char *command){
		if (strcmp(command,"ls") == 0){
				sendCommand("ls");
		}
		if (strcmp(command,'cd') == 0){
				
		}
}
