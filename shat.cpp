#include <openssl/sha.h>
#include <bits/stdc++.h>

using namespace std;


int main(){

	string filename;

	cout<<"Enter FileName: ";
	cin>>filename;

	char file[filename.length()+1];
    strcpy(file,filename.c_str());

    FILE *fp = fopen(file,"rb");
    if(fp==NULL){

        printf("File open error");
        return 1;
    }


    FILE *fpd = fopen("sha_digest","a");

    if(fpd==NULL){

        printf("File open error");
        return 1;
    }
    int count=1;

    char data[524289]={0};

    while(fgets (data , 524288 , fp)){
    	fseek ( fp , 524288 , SEEK_CUR );

		cout<<count++<<"\n";

	    char buf[21];

	    size_t length = 524288;

		unsigned char hash[SHA_DIGEST_LENGTH]={'\0'};

		SHA1((unsigned char*)data, length, hash);

		for (int i=0; i < 10; i++) {
			sprintf((char*)&(buf[i*2]), "%02x", hash[i]);
		}
		//buf[21] = '\n';
		fputs (buf,fpd);
		memset(data,0,524289);

    }

	return 0;
}
