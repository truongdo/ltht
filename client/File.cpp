class File{
		char fname[20];
		int fid;
		char *sharing;
		public:
			File(char *name,int id);
			char* getName(){
				return dname;
			}
			int getFid(){
				return did;
			}
}
