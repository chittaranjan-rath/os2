#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string.h>
using namespace std;
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
int main(int argc, char** argv){
	fileSize=getFilesize(argv[1]);
	cout<<"\n filesize of "<<argv[1]<<" is "<<fileSize<<"B"<<endl;
	no_of_chunks = fileSize/5;
	FILE *file = fopen(argv[1], "rb");
	FILE *file1 = fopen("shaout.txt", "a");
	printf("1\n");
	printf("no of chunks =%d\n",no_of_chunks);

	 char data[6]={'\0'};
	 while(fgets(data , 5 , file)){
			 fseek ( file, 5, SEEK_CUR );
			 //data[6]='\0';
			 cout<<"strlen of data is "<<strlen(data);
			 unsigned char hash[SHA_DIGEST_LENGTH];
			 SHA1((unsigned char*)data, strlen(data), (unsigned char*)&hash);
			 	//SHA1((unsigned char*)data, sizeof(data), hash);
		 //chunkHash = computeSHAforChunk(chunk);
		 //chunkHash = chunkHash.substr(0,20);
		 //totalHash.append(chunkHash);

 		size_t s = sizeof(hash);
	/*	for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
				 sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	 	}*/
		char buf[SHA_DIGEST_LENGTH*2+1];
 		for (int i=0; i < SHA_DIGEST_LENGTH; i++) {
 			//printf("%s\n", );
 			sprintf(&(buf[i*2]), "%02x", (unsigned int)hash[i]);
 		}
		char sbuf[21];
		for(int i=0;i<20;i++)
			sbuf[i]=buf[i];
		sbuf[20]='\0';
 		fputs (sbuf,file1);
 		memset(data,0,6);
	 }


}
