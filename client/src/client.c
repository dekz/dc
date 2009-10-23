#include "client.h"

struct sockaddr_in server;
bool welcome_message_printed = FALSE;
char auth[MAX_AUTH_SIZE + MAX_AUTH_SIZE + 1];
int sock = -1;

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
  if(fgets(message, size, stdin) == NULL)
  {
    perror("fgets");
		exit(1);
  }
  chomp(message);
}

void auth_prompt()
{
	if(strlen(auth) == 0)
	{	
		char username[MAX_AUTH_SIZE];
		char password[MAX_AUTH_SIZE];
	
		prompt("Username: ", username, MAX_AUTH_SIZE);
		prompt("Password: ", password, MAX_AUTH_SIZE);
	
		snprintf(auth, MAX_AUTH_SIZE*2+1, "%s\r%s", username, password);
	}
}

bool authenticated()
{
	auth_prompt(auth);

	char response[MAX_MESSAGE_SIZE];
	
	if(send_message(auth))	
	{
		if(receive_message(response)) {
			if(strcmp(response, "1") == 0)
				return TRUE;
		}
	}
	
	return FALSE;
}

void lookup_player()
{
  char message[MAX_MESSAGE_SIZE];
  char buffer[MAX_MESSAGE_SIZE];

	prompt("What player would you like to look up? ", message, MAX_MESSAGE_SIZE);
  printf("Looking up '%s'\n", message);

  if(send_message(message))
  {
    if(receive_message(buffer))
    {
      printf("%s\n", buffer);
    }
  }
}

void communicate()
{
	socket_start();
	
	if(sock >= 0)
  {
	  while(1) 
	  {
			socket_connect();
			print_welcome_message();
			if(authenticated()) {
				lookup_player(socket);
			} else {
				printf("Incorrect authentication details!\n");
				return;
			}
			
      close(socket);
		}
  } else {
		perror("socket_start");
		return;
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

int main()
{
	communicate();
  return 0;
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