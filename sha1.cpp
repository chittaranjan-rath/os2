#include <openssl/sha.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>
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

char *readFile(char *fileName,size_t n,FILE *file)
{
	
	char *code;
	size_t n1 = 0;
	int c;

	if (file == NULL)
        	return NULL; //could not open file

	code = (char *)malloc(524289);
	
    	while (n1<524288 &((c = fgetc(file)) != EOF)) 
    	{
		
        	code[n1++] = (char) c;
    	}

    	code[n1] = '\0';        

    	return code;
}
int main(int argc, char** argv)
{  
 
	unsigned char * str;//[1000000]; //= "Original String";
	//unsigned char hash[20]; // == 20
	printf("SHA is \n");
	//SHA1(str, sizeof(str) - 1, hash);
	
	//unsigned char* cp = hash;
	/*for ( ; *cp != '\0'; ++cp ){
  		printf("%02x", *cp);
	}*/
	fileSize=getFilesize(argv[1]);
	cout<<"\n filesize of "<<argv[1]<<" is "<<fileSize<<"B"<<endl;
	no_of_chunks = fileSize/524288;
	FILE *file = fopen(argv[1], "r");
	FILE *file1 = fopen("shaout.txt", "w");
	printf("1\n");
	printf("no of chunks =%d\n",no_of_chunks);
	for(i=0;i<no_of_chunks;i++){
		unsigned char hash[524289];
		printf("10\n");
		str = (unsigned char *)readFile("sample.txt",0, file);
		printf("11\n");
		SHA1(str, sizeof(str) - 1, hash);
		printf("111\n");
		fputs ((const char *)hash , file1);
			printf("1111\n");
		//printf("%s\n",readFile("sample.txt",0));
		//fputs (readFile("sample.txt",0,file) , file1);
	}	
	if(fileSize-(no_of_chunks*524288)>0){
		unsigned char * hash;
		printf("10\n");
		str = ( unsigned char *)readFile("sample.txt",0 , file);
		printf("110\n");
		SHA1(str, sizeof(str) - 1, hash);
		printf("1110\n");
		fputs ((const char *)hash , file1);
		printf("1110\n");
	}
	fclose(file);
	fclose(file1);

  	return 0;
}



	
	
	
