#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string.h>
using namespace std;
#define CHUNK_SIZE 524288
unsigned long long fileSize;
unsigned long long no_of_chunks;
unsigned long long i;
size_t getFilesize(const char* filename) {
	struct stat st;
	if(stat(filename, &st) != 0) {
		return 0;
    	}
    	return st.st_size;
}
string computeSHAforChunk(char *chunk){//string str){
	unsigned char digest[SHA_DIGEST_LENGTH];
	string retHash;
	 //SHA1((unsigned char*)data, strlen(data), (unsigned char*)&hash);
	SHA1((unsigned char*)chunk, strlen(chunk), (unsigned char*)&digest);
	//SHA1((unsigned char*)str.c_str(), str.length(), (unsigned char*)&digest);
	if(strlen((char *)digest) == 0){
		cout<<"Unable to calculate hash"<<endl;
		return NULL;
	}
   char mdString[SHA_DIGEST_LENGTH*2+1];

   for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	}
	retHash = mdString;
	return retHash;
}


string computeSHAforFile(char * filename){
	string totalHash, chunkHash;
	char chunk[CHUNK_SIZE+1];
	int len,i=0;
	char ch;
	//FILE *srcFile = fopen((char *)filename.c_str(), "rb");
	FILE *srcFile = fopen(filename, "rb");
	if(srcFile == NULL){
		cout<<"Unable to open file "<<filename<<endl;
		return NULL;
	}
	cout<<"1";
	while(fgets(chunk , CHUNK_SIZE , srcFile)){
    	fseek ( srcFile, CHUNK_SIZE, SEEK_CUR );
		chunkHash = computeSHAforChunk(chunk);
		chunkHash = chunkHash.substr(0,20);
		totalHash.append(chunkHash);
		i++;
		memset(chunk, 0, CHUNK_SIZE);
	}
}
int main(int argc, char** argv){
		fileSize=getFilesize(argv[1]);
		cout<<"\n filesize of "<<argv[1]<<" is "<<fileSize<<"B"<<endl;
		cout<<"gf urselasd";
		//no_of_chunks = fileSize/524288;
		cout<<"!!";
	string hash1;
	hash1=computeSHAforFile(argv[1]);
	cout<<"hash is "<<hash1<<endl;
/*char data[]={'b'};
string retHash;
data[1]='\0';
	unsigned char digest[SHA_DIGEST_LENGTH];
	cout<<"hash not calulatede"<<endl;
//SHA1('b', 1, (unsigned char*)&digest);
cout<<"len is "<<strlen(data);
SHA1((unsigned char*)data, strlen(data), (unsigned char*)&digest);
cout<<"hash calulatede"<<endl;
for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
  printf("%02x", (unsigned int)digest[i]);
    // sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
}*/
return 0;
}
