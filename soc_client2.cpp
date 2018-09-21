#include "2.cpp"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include<vector>
#include<iostream>
#include<arpa/inet.h> //inet_addr
#include<ctype.h>
#include<string>
using namespace std;
  pthread_t tid[50];
void * cientThread(void *arg)
{
  printf("In thread with id \n");
  pthread_t id = pthread_self();
  for(int k=0;k<50;k++){
    if(pthread_equal(id,tid[k]))
    {
        printf("\n %d thread processing\n",k+1);
    }
  }
  char message[1000];
  char buffer[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  // Create the socket.
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  //Configure settings of the server address
 // Address family is Internet
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function
  serverAddr.sin_port = htons(8888);
 //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0)
    {
        printf("connect failed. Error\n");
        //return 1;
    }

  //  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    strcpy(message,"bhak");
  /* if( send(clientSocket , message , strlen(message) , 0) < 0)
    {
            printf("Send failed\n");
    }*/
      write(clientSocket , message , strlen(message));
    //Read the message from the server into the buffer
    /*if(recv(clientSocket, buffer, 1024, 0) < 0)
    {
       printf("Receive failed\n");
    }*/
    char tempbuffer[100];
    read(clientSocket,tempbuffer,100);
    printf("Data received: %s with tid \n",tempbuffer);
    strcpy(tempbuffer,"close");
    write(clientSocket , buffer , strlen(buffer));
    //Print the received message

     id = pthread_self();
     cout<<"sockeet is "<<clientSocket<<endl;
    /*if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }*/
    close(clientSocket);
    pthread_exit(NULL);
}
vector<pair<string, string>> getFileNameFromMtorrent(char * mtorrentfile){
    vector<pair<string, string>> vec;
  	FILE *fileread = fopen(mtorrentfile, "r");
    if(fileread == NULL){
  		cout<<"Unable to open file "<<mtorrentfile<<endl;
  		return vec;
  	}
    int c,cnt=0;
    char fname[1000];char fsize[1000];
    fgets(fname , 100000 , fileread);
    //fseek (fileread, CHUNK_SIZE, SEEK_CUR );
    fgets(fname , 100000 , fileread);
    fgets(fname , 100000 , fileread);
    fgets(fsize , 100000 , fileread);

    //cout<<fname<<endl;
    //cout<<fsize<<endl;
    vec.push_back(make_pair(fname,fsize));
    return vec;
}
void connectToPeers(vector< pair<string, string> > seederList){
  int size=seederList.size();
  cout<<"connect to peers1"<<endl;
  cout<<"seederList size is "<<size<<endl;
  int i = 0;

  while(i< size)
  {
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
//  sleep(20);
  i = 0;
  while(i< size)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }
  //return 0;
/*  int i = 0;
  pthread_t tid[51];
  while(i< 50)
  {
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
  sleep(20);
  i = 0;
  while(i< 50)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }
  */


}
int dload(char *mtorrentfilename){
  //connectToTracker();
  vector< pair<string, string> > seederList;
  seederList.push_back(make_pair("127.0.0.1","7071"));
  seederList.push_back(make_pair("127.0.0.1","7072"));
  seederList.push_back(make_pair("127.0.0.1","7073"));
  char mtorrentfile[1000];
  strcpy(mtorrentfile,mtorrentfilename);
  vector< pair<string, string> > fileDetails;
  fileDetails=getFileNameFromMtorrent(mtorrentfile);
  cout<<"connect to peers"<<endl;
  connectToPeers(seederList);
  cout<<"returned to peers"<<endl;
  return 0;
}
char * processInput(string input,int len){
 int i,j=0;char * in1;
  for(i=0;i<len;i++){
    if (!isspace(input.at(i))){
        in1[j]=input[i];
        j++;
    }
    else
      break;
  }
  in1[j]='\0';
  return in1;
}
int main(){
  cout<<"Press any key to quit"<<endl;
  string input;
//  cout<<"!";
  cin>>input;
  //getline(cin,input);
  cout<<"!@@@";
  //cin>>input;
  int len = input.length();
  cout<<len<<endl;
  //cout<<strlen((char *)input.c_str());
  while(len!=1){
    char * finput;
    finput = processInput(input,len);
    printf("finput is %s\n",finput );
    if(strcmp(finput,"share")==0){
          cin>>input;len = input.length();
          char * fname = processInput(input,len);
          //printf("filename  is %s\n",fname);
          char filename[100];
          strcpy(filename, fname);
          cin>>input;len = input.length();
          char * filename1 = processInput(input,len);
          //printf("mtorr name  is %s\n",filename1 );
          string hash1= pmain(filename,filename1);
          //addToSeederList(hash1,filename);
    }
    if(strcmp(finput,"get")==0){
          cin>>input;len = input.length();
          char * fname = processInput(input,len);
          //printf("filename  is %s\n",fname);
          char mtorrentfilename[100];
          strcpy(mtorrentfilename, fname);
          cin>>input;len = input.length();
          char * destination = processInput(input,len);
          //printf("mtorr name  is %s\n",filename1 );
          int t = dload(mtorrentfilename);
          if(t==0)
          cout<<"download of "<<mtorrentfilename<<" is complete"<<endl;
          else
          cout<<"download failed"<<endl;
    }
    //cout<<"in length "<<len<<endl;
    fflush(stdin);
    cin>>input;
    len = input.length();

  }
  exit(0);
  //int t =connectToServer();
  return 0;





  int i = 0;
  pthread_t tid[51];
  while(i< 50)
  {
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
  sleep(20);
  i = 0;
  while(i< 50)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }
  return 0;
}
