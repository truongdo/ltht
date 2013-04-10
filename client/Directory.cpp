#include "Directory.h"

char* Directory::getName()
{
		return Directory::dname;
}
int Directory::getId(){
		return Directory::did;
}
int Directory::getPId(){
		return Directory::parentDId;
}
int Directory::getCount(){
		return Directory::listSubDir.size();
}
Directory Directory::getSubDir(int idx){
		return Directory::listSubDir[idx];
}
void Directory::setName(char* name){
		Directory::dname = name;
}
void Directory::setDirList(vector<Directory> listDir){
		Directory::listSubDir = listDir;
}
void Directory::setId(int id){
	Directory::did = id;
}
void Directory::setPId(int did1){
	Directory::parentDId = did1;
}
Directory::Directory(){
	
}
