#include "client.h"

int socket_start()
{
    int sock;
    struct sockaddr_in server;
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

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
      perror("connect");
      exit(1);
    }
    
    return sock;
}

void prompt(char *message, char *response, int size)
{
	printf("%s", message);
  if(fgets(message, size, stdin) == NULL)
  {
    perror("fgets");
		exit(1);
  }
  chomp(message);
}

void get_auth_details(char *username, char *password, char* auth)
{
	prompt("Username: ", username, MAX_AUTH_SIZE);
	prompt("Password: ", password, MAX_AUTH_SIZE);
	
	snprintf(auth, MAX_AUTH_SIZE*2+1, "%s\r%s", username, password);
}

bool authenticated(char* auth, int socket) {
	char response[MAX_AUTH_SIZE];
	
	if(send_message(socket, auth))	
	{
		if(receive_message(socket, response)) {
			if(strcmp(response, "1") == 0)
				return TRUE;
		}
	}
	
	return FALSE;
}

void communicate(char* auth, int socket) {
  char message[MAX_MESSAGE_SIZE];
  char buffer[MAX_MESSAGE_SIZE];
	bool should_print = TRUE;


  while(1) 
  {
    if((socket = socket_start()) >= 0)
    {
			print_welcome_message(socket, should_print);
			should_print = FALSE;
	
			if(authenticated(auth, socket)) {
				memset(message, 0, MAX_MESSAGE_SIZE);
				memset(buffer,  0, MAX_MESSAGE_SIZE);

				prompt("What player would you like to look up? ", message, MAX_MESSAGE_SIZE);
			  printf("Looking up '%s'\n", message);

	      if(send_message(socket, message))
	      {
	        if(receive_message(socket, buffer))
	        {
	          printf("%s\n", buffer);
	        }
	      }
			} else {
				printf("Incorrect authentication details!\n");
				return;
			}
      close(socket);
    } else {
			perror("socket_start");
			return;
		}
  }
}

void print_welcome_message(int socket, bool should_print) 
{
	char welcome[MAX_MESSAGE_SIZE];
	if(receive_message(socket, welcome)) {
		if(should_print)
			printf("%s", welcome);
	}
}

int main()
{
	char auth[MAX_AUTH_SIZE * 2 + 1];
	char username[MAX_AUTH_SIZE];
	char password[MAX_AUTH_SIZE];
  int socket;
  
	get_auth_details(username, password, auth);
	communicate(auth, socket);
	    
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
  if (recv(sockfd, buf, MAX_MESSAGE_SIZE, 0) == -1)
  {
    perror("recv");
    exit(1);
  }

  return TRUE;
}