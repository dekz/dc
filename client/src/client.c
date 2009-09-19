#include "client.h"


int main()
{
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	char *message="TEST\n\r";
	

	address.sin_family = AF_INET;
	address.sin_port = htons(7000);
	//proper way to attach address?
	
	connect(client_socket, &address, sizeof(address));

	sleep(10);
	printf("trying to send %s\n", message);
	send(client_socket,message,strlen(message),0);
	
	close(client_socket);


	exit(0);
}