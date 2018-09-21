#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <string.h>
#include <algorithm>
#include <assert.h>
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
string computeSHAforChunk(char *chunk){
	unsigned char hashval[SHA_DIGEST_LENGTH];
	string retVal;
	SHA1((unsigned char*)chunk, strlen(chunk)-1, (unsigned char*)&hashval);
	if(strlen((char *)hashval) == 0){
		cout<<"Unable to calculate hash"<<endl;
		return NULL;
	}
   char temp[SHA_DIGEST_LENGTH*2+1];

   for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
        sprintf(&temp[i*2], "%02x", (unsigned int)hashval[i]);
	}
	retVal = temp;
	return retVal;
}


string computeSHA(char * filename,char *filename2,unsigned long long fileSize){
	string fileHashValue, chunkHashValue;
	char chunk[CHUNK_SIZE+1];
	int len,i=0;
	char ch;
	//FILE *fileread = fopen((char *)filename.c_str(), "rb");
	FILE *fileread = fopen(filename, "rb");
	FILE *filewrite = fopen(filename2, "a");
	fputs ("127.0.0.1 8888 ",filewrite);
	fputs ("\n",filewrite);
	fputs ("127.0.0.1 7777 ",filewrite);
	fputs ("\n",filewrite);
	fputs (filename,filewrite);
	fputs ("\n",filewrite);
	//fputs (" ",filewrite);
	const int n = snprintf(NULL, 0, "%llu", fileSize);
	assert(n > 0);
	char buf[n+1];
	int c = snprintf(buf, n+1, "%llu", fileSize);
	assert(buf[n] == '\0');
	assert(c == n);


	fputs (buf,filewrite);
	fputs ("\n",filewrite);
	//fputs (" ",filewrite);
	if(fileread == NULL){
		cout<<"Unable to open file "<<filename<<endl;
		return NULL;
	}
	cout<<"1";char sbuf[21];
	while(fgets(chunk , CHUNK_SIZE , fileread)){
    	fseek ( fileread, CHUNK_SIZE, SEEK_CUR );
				cout<<"size of chunk is "<<strlen(chunk)<<endl;
		chunkHashValue = computeSHAforChunk(chunk);
		chunkHashValue = chunkHashValue.substr(0,20);


		for(int i=0;i<20;i++)
			sbuf[i]=chunkHashValue[i];
		sbuf[20]='\0';
		fputs (sbuf,filewrite);
		fileHashValue.append(chunkHashValue);
		i++;

		memset(sbuf, 0, 21);
		memset(chunk, 0, CHUNK_SIZE);
	}

	fclose(fileread);
	fclose(filewrite);
	return fileHashValue;
}
string pmain(char * filename,char *filename2){
		fileSize=getFilesize(filename);
		cout<<"receivev "<<filename<<" and "<<filename2<<endl;
		cout<<"\n filesize of "<<filename<<" is "<<fileSize<<"B"<<endl;
		//no_of_chunks = fileSize/524288;
		cout<<"!!";
	string hash1;

	hash1=computeSHA(filename,filename2,fileSize);
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
return hash1;
}
