
class FileReceiver(){
	ostream myfile;
	string filename;
	int sockfd;
	public:
		FileReceiver(int sock);
		int recevFile(filename);
}

FileReceiver::FileReceiver(int sock){
	sockfd = sock;
}

FileReceiver::recevFile(string fn){
	filename = fn;
	
}
