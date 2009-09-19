#include "server.h"

/*
socket() create a new socket and return its descriptor
bind() associate a socket with a port address
listen() establish a queue for connection requests
accept() accept a connection request
connect() initiate a connection to a remote host
recv() recieve data from a socket desciptor 
send() send data to a socket descriptor
close() one way close of socket descriptor

# SOCK_STREAM --- TCP protocol.
# SOCK_DGRAM --- UDP protocol.
# SOCK_RAW --- IP protocol.

*/

int main()
{
	load_data();
	load_users();

	int dcsocket;
	int addrlen;
	int socket_current;
	struct sockaddr_in dcserver;
	struct sockaddr_in dcclient;
	char buf[100];
	char *message = "SEND MESSAGE A";
	printf("Creating Socket...\n");
	
	if ((dcsocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket \n");
	}
	

	memset(&dcserver, 0, sizeof(dcserver));
	dcserver.sin_family = AF_INET;
	dcserver.sin_addr.s_addr = INADDR_ANY;
	dcserver.sin_port = htons(7000);
	
	/* bind the socket to the port number */
	if (bind(dcsocket, (struct sockaddr *) &dcserver, sizeof(dcserver)) == -1) {
		perror("bind");
		exit(1);
	}

	printf("Waiting for connections...\n");
	if (listen(dcsocket, 5) == -1)
	{
		printf("listen\n");
		exit(1);
	}
	
	addrlen = sizeof(dcclient);
	printf("Accepting Connections...\n");
	if ((socket_current = accept(dcsocket, (struct sockaddr *) &dcclient, &addrlen)) == -1)
	{
		printf("accept\n");
			exit(1);
	}


	if (recv(socket_current, buf, sizeof(buf), 0) == -1)
	{
		printf("recv\n");
		exit(1);
	}


	printf("Recieved Message: %s\n", buf);
	
	printf("Sending message %s\n", message);
	
	if (send(socket_current, message, strlen(message), 0) == -1)
	{
		printf("send\n");
		exit(1);
	}


	close(socket_current);
	close(dcserver);
	close(dcclient);
	
	exit(0);
}