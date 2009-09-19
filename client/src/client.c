#include "client.h"

#define HOST "localhost"

int main()
{
	int client_socket;
	char *message="TEST\n\r";
	struct sockaddr_in dcserver;
	struct sockaddr_in dcclient;
	struct hostent *hp;
	char buf[100]; 
	printf("attempting to get host name\n");
	if ((hp = gethostbyname(HOST)) == 0) {
		printf("Can't get host name\n");
		exit(1);
	}
	
	memset(&dcserver, 0, sizeof(dcserver));
	
	dcserver.sin_family = AF_INET;
	dcserver.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	dcserver.sin_port = htons(7000);
	//proper way to attach address?
	printf("Attempting to connect");
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	
	/* connect to PORT on HOST */
	if (connect(client_socket,(struct sockaddr *)  &dcserver, sizeof(dcserver)) == -1) {
		perror("connect");
		exit(1);
	}
	
	if (send(client_socket, message, strlen(message), 0) == -1) {
		perror("send");
		exit(1);
	}
	
 /* wait for a message to come back from the server */
    if (recv(client_socket, buf, 100, 0) == -1) {
            perror("recv");
            exit(1);
    }

	printf("%s\n", buf);

	
	close(client_socket);


	exit(0);
}