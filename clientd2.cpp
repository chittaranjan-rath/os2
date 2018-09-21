
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

void * cientThread(void *arg)
{
  long int tid = pthread_self();
  printf("In thread with id %ld\n",tid);

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
  printf("checkpount 0 %ld\n",tid );
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
printf("checkpount 1 %ld \n",tid );
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0)
    {
        printf("connect failed. Error\n");
        //return 1;
    }
      printf("checkpount 2 %ld\n",tid );
   long int id=pthread_self();
   string ids=to_string(id);

  //  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    strcpy(message,"bhak ");
    strcat(message,ids.c_str());
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
    printf("Data received: %s with tid %ld\n",tempbuffer,pthread_self());
      char tempbuffer1[100];
    strcpy(tempbuffer1,"close");
    write(clientSocket , tempbuffer1 , strlen(tempbuffer1));
    //Print the received message


     cout<<"sockeet is "<<clientSocket<<endl;
    /*if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }*/
    //sleep(6);
    close(clientSocket);
    pthread_exit(NULL);
}

void connectToPeers(vector< pair<string, string> > seederList){
  int size=seederList.size();
  cout<<"connect to peers1"<<endl;
  cout<<"seederList size is "<<size<<endl;
  int i = 0;
  pthread_t tid[size+1];
  while(i< size)
  {
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    //i++;
    //pthread_join(tid[i],NULL);
    sleep(5);
    printf("%d:\n",i);
    i++;
  }
  i = 0;
  while(i< size)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }



}

int main(){

  vector< pair<string, string> > seederList;
  seederList.push_back(make_pair("127.0.0.1","7071"));
  seederList.push_back(make_pair("127.0.0.1","7072"));
  seederList.push_back(make_pair("127.0.0.1","7073"));
  //seederList.push_back(make_pair("127.0.0.1","7073"));
  //  seederList.push_back(make_pair("127.0.0.1","7073"));
  connectToPeers(seederList);

  return 0;
}
