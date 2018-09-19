/*
    C ECHO client example using sockets
*/
//#include<stdio.h> //printf
///#include<string.h>    //strlen
#include "2.cpp"
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <unistd.h>
#include <ctype.h>
using namespace std;
int createSocket(){
  int sock = socket(AF_INET , SOCK_STREAM , 0);
  if (sock == -1)
  {
      printf("Could not create socket");
  }
  printf("Socket created\n");
  return sock;
}
void prepSockAddr(struct sockaddr_in * server){
  (*server).sin_family = AF_INET;
  (*server).sin_addr.s_addr = inet_addr("127.0.0.1");
  //server.sin_addr.s_addr = INADDR_ANY;
  (*server).sin_port = htons( 8888 );

}
void prepMsgToSend(char * message){
  scanf("%s" , message);
}
int connectToServer(char * message){
  int sock;
  struct sockaddr_in server;
  char  server_reply[2000];
  //char message[1000];
  //Create socket
  sock=createSocket();

  prepSockAddr(&server);

  //Connect to remote server
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
      perror("connect failed. Error");
      return 1;
  }

  printf("Connected\n");

  //keep communicating with server
  while(1)
  {
      printf("Enter message : ");
      //scanf("%s" , message);
      //prepMsgToSend(message);




      if( send(sock , message , strlen(message) , 0) < 0)
      {
          printf("Send failed\n");
          return 1;
      }

      //Receive a reply from the server
      if( recv(sock , server_reply , 2000 , 0) < 0)
      {
          printf("recv failed\n");
          break;
      }

      printf("Server reply :");
      for(int i=0;i<strlen(server_reply);i++)
      printf("%c",server_reply[i]);
      printf("\n");
      return 0;
  }

  close(sock);
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
  //printf("input 1 is %s\n",in1 );

    /*char *token;
  	token = strtok ((char *)input.c_str()," ");
  	while (token != NULL ){
  		cout<<token<<endl;
  		token = strtok (NULL, " ");
  	}
    */

  return in1;
}
void  addToSeederList(string hash,char *filename) {
  char *ip = "127.0.0.1 8888 ";
//if the string is stored in a variable, and you need to make a copy of the string then you can use strcpy() function
  int lenofmsgtosend= strlen(ip) +hash.length()+strlen(filename)+4;
 char *msgtosend = new char(lenofmsgtosend + 1);
 strcpy(msgtosend, ip);

   strcat(msgtosend, (char *)hash.c_str());
    strcat(msgtosend, " ");
    strcat(msgtosend, filename);
    printf("msg is %s\n",msgtosend);
    char msg[100000];
      strcpy(msg, msgtosend);
  int t =connectToServer(msg);
  delete [] msgtosend;
}
int main()
{
    cout<<"Press any key to quit"<<endl;
    string input;
    cout<<"!";
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
            addToSeederList(hash1,filename);
      }
      //cout<<"in length "<<len<<endl;
      fflush(stdin);
      cin>>input;
      len = input.length();

    }
    exit(0);
    //int t =connectToServer();
    return 0;
}
