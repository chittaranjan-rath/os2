/*
    C socket server example
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

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
int readmsgfromClient(int client_sock,char *client_message){
  int read_size;
  while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
  {
      printf("Received msg :\n" );
      for(int i=0;i<strlen(client_message);i++)
      printf("%c",client_message[i]);
      printf("\n");
    //  printf("received msg: %s\n",client_message);
      //Send the message back to client
      write(client_sock , client_message , strlen(client_message));
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
