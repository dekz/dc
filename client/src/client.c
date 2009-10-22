#include "client.h"

int socket_start()
{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;

    printf("Attempting to get hostname...\n");
    if ((hp = gethostbyname(HOST)) == 0)
    {
      perror("get host name");
      exit(1);
    }

    printf("Got hostname.\n");

    /*
     * copy the network address part of the structure to the 
     * sockaddr_in structure which is passed to connect() 
     */

    server.sin_family = AF_INET;
    server.sin_port = PORT;
    memcpy(&server.sin_addr, hp->h_addr_list[0], hp->h_length);
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      exit(1);
    }

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
      perror("connect");
      exit(1);
    }
    
    return sock;
}

int main()
{
  char *message = "Mille";
  char buffer[PLAYER_INFO_LENGTH];
  int socket;
  
  welcome_message();
 
  // while(1) 
  // {
    if((socket = socket_start()) >= 0)
    {
      if(send_message(socket, message) == TRUE)
      {
        if(receive_message(socket, buffer) == TRUE)
        {
          printf("%s\n", buffer);
        }
      }
      close(socket);
    } // else break;
    //   }

  return 0;
}

int send_message(int sockfd, char *msg)
{
  if (send(sockfd, msg, strlen(msg), 0) == -1)
  {
    perror("send");
    exit(1);
  }
  return TRUE;
}

int receive_message(int sockfd, char *buf)
{
  if (recv(sockfd, buf, PLAYER_INFO_LENGTH, 0) == -1)
  {
    perror("recv");
    exit(1);
  }

  return TRUE;
}