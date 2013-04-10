#include <vector>
#include "Directory.h"
class DirectoryList{
		vector<Directory> DList;
		public:
			Directory getCurrentDir();
			void goBack();
			void goForward(Directory dir);
};
