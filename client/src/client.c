#include "client.h"


int main()
{
	int client_socket;
	char *message="TEST\n\r";
	struct sockaddr_in dcserver;
	struct sockaddr_in dcclient;
	struct hostent *hp;
	char buf[100]; 
	
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((char *) &dcserver, sizeof(dcserver));
	
	dcserver.sin_family = AF_INET;
	dcserver.sin_port = htons(7000);
	//proper way to attach address?

	sleep(10);	
	connect(client_socket, &dcserver, sizeof(dcserver));
	
	write(client_socket, message, sizeof(message));
	
	bzero(buf, sizeof(buf));
	read(client_socket, buf, 100);
	printf("C: %s\n", buf);

	
	close(client_socket);


	exit(0);
}