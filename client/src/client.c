#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "helpers.h"
#include "client.h"

struct sockaddr_in server;
bool welcome_message_printed = FALSE;
char auth[MAX_AUTH_SIZE + MAX_AUTH_SIZE + 1];
int sock = -1;

int main()
{
  while(1) 
  {
		socket_start();
		
		if(sock >= 0)
	  {
			print_welcome_message();
			lookup_player();
      close(sock);
			sock = -1;
	  } else {
			perror("socket_start");
			return 1;
		}
	}
	
	return 0;
}

void socket_start()
{
    struct hostent *hp;

    debug("Attempting to get hostname...");
    if ((hp = gethostbyname(HOST)) == 0)
    {
      perror("get host name");
			exit(1);
    }

    debug("Got hostname.");

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

		socket_connect();
}

void socket_connect() {
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
  {
    perror("connect");
    exit(1);
  }
}

void prompt(char *message, char *response, int size)
{
	printf("%s", message);
	
  if(fgets(response, size, stdin) == NULL)
  {
    perror("fgets");
		exit(1);
  }
  chomp(response);
}

void auth_prompt()
{
	if(strlen(auth) == 0)
	{	
		char username[MAX_AUTH_SIZE];
		char password[MAX_AUTH_SIZE];
	
		prompt("Username: ", username, sizeof(username));
		prompt("Password: ", password, sizeof(password));
	
		snprintf(auth, MAX_AUTH_SIZE*2+1, "%s\t%s", username, password);
	}
}


void lookup_player()
{
	int size = MAX_MESSAGE_SIZE+MAX_AUTH_SIZE+MAX_AUTH_SIZE+2;
	char player[MAX_MESSAGE_SIZE];
	char message[size];
  char buffer[MAX_MESSAGE_SIZE];

	auth_prompt();

	prompt("What player would you like to look up? ", player, MAX_MESSAGE_SIZE);
  printf("Looking up '%s'\n", player);

	snprintf(message, size, "%s\t%s", auth, player);

  if(send_message(message))
  {
    if(receive_message(buffer))
    {
			if(strcmp("1", buffer))
			{
				printf("'%s' not found amongst the batting figures.\n", player);
				printf("Please check your spelling and try again.\n");
			} else if(strcmp("2", buffer)) {
				printf("Invalid authentication details. Try again.\n");
				memset(auth, 0, MAX_AUTH_SIZE*2+1);
			} else {
				printf("%s\n", buffer);
			}
    }
  }

}

void print_welcome_message() 
{
	char welcome[MAX_MESSAGE_SIZE];
	if(receive_message(welcome)) {
		if(!welcome_message_printed)
		{
			printf("%s\n", welcome);
			welcome_message_printed = TRUE;
		}
	}
}



int send_message(char *msg)
{
  if (send(sock, msg, strlen(msg), 0) == -1)
  {
    perror("send");
    exit(1);
  }
  return TRUE;
}

int receive_message(char *buf)
{
  if (recv(sock, buf, MAX_MESSAGE_SIZE, 0) == -1)
  {
    perror("recv");
    exit(1);
  }

  return TRUE;
}