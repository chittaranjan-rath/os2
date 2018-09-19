/*
    C socket server example
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<ctype.h>
#include<iostream>
using namespace std;
struct TrackerContent
{
  char * IpAddress;
	char * port;
	int iport;
  //pointer to 20 byte data buffers of the sha1sum of each of the pieces:
  char * piece_hashes;
  char * file_Name;
}trackerContent1;
int createSocket(){
int socket_desc;
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1)
  {
      printf("Could not create socket\n");
  }
  printf("Socket created\n");
  return socket_desc;
}
void prepSockAddr(struct sockaddr_in * server){
  (*server).sin_family = AF_INET;
  (*server).sin_addr.s_addr = inet_addr("127.0.0.1");
  //server.sin_addr.s_addr = INADDR_ANY;
  (*server).sin_port = htons( 8888 );

}
int binding(int socket_desc,struct sockaddr_in * server){
  if( bind(socket_desc,(struct sockaddr *)server , sizeof(*server)) < 0)
  {
      //print the error message
      perror("bind failed. Error");
      return 1;
  }
  printf("bind done\n");
  return 0;
}
void writeToFile(struct TrackerContent  t){
  	FILE *filewrite = fopen("seederList.txt", "a");
    fputs (t.IpAddress,filewrite);
    fputs (" ",filewrite);
    fputs (t.port,filewrite);
    fputs (" ",filewrite);
    fputs (t.piece_hashes,filewrite);
    fputs (" ",filewrite);
    fputs (t.file_Name,filewrite);
    fclose(filewrite);
}
int readmsgfromClient(int client_sock,char *client_message){
  int read_size;
  while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
  {
      printf("Received msg :\n" );
      for(int i=0;i<strlen(client_message);i++)
      printf("%c",client_message[i]);
      printf("\n");
      char *token;int cnt=0;char ip[20];char port[6];char hash[10000];char filename[100];
    	token = strtok ((char *)client_message," ");
    	while (token != NULL ){
        if(cnt==0)
        strcpy(ip,token);
        if(cnt==1)
        strcpy(port,token);
        if(cnt==2)
        strcpy(hash,token);
        if(cnt==3)
        strcpy(filename,token);
    		cout<<token<<endl;
        cnt++;
    		token = strtok (NULL, " ");
    	}
      trackerContent1.IpAddress = ip;
      trackerContent1.port = port;
      trackerContent1.iport = atoi(port);
      trackerContent1.piece_hashes = hash;
      trackerContent1.file_Name = filename;
      writeToFile(trackerContent1);
    /*  int i,j=0;char * in1;int cnt=0;
      for(int i=0;i<strlen(client_message);i++){
        if (!isspace(input.at(i))){
            in1[j]=input[i];
            j++;
        }
        else{
          in1[j]='\0';
          j=0;
          cnt++;
        }
          //break;
      }
      */
          //  printf("received msg: %s\n",client_message);
      //Send the message back to client
      //write(client_sock , client_message , strlen(client_message));
      write(client_sock , "msg received" , strlen(client_message));
      memset(client_message, NULL, 2000);
  }
  return read_size;
}
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    //Create socket
    socket_desc = createSocket();
    //Prepare the sockaddr_in structure
    prepSockAddr(&server);
    //Bind
    int t= binding(socket_desc,&server);
    //Listen
    listen(socket_desc , 3);
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    printf("Connection accepted\n");
    memset(client_message, NULL, 2000);
    //Receive a message from client
     read_size = readmsgfromClient(client_sock,client_message);
    if(read_size == 0)
    {
        printf("Client disconnected\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    return 0;
}
