#include <vector>

using namespace std;
class Directory{
		char *dname;
		int did;
		int parentDId;
		vector<Directory> listSubDir;
		
		//vector<File> fileList;
		public:
			Directory();
			Directory getSubDir(int idx);
			int getId();
			int getPId();
			int getCount();
			char* getName();
			void setId(int id);
			void setPId(int pdid);
			void setName(char* name);
			void setDirList(vector<Directory> listDir);
			
};
