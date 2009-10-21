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
	int opt=TRUE;
	int dcsocket;
	int addrlen;
	int socket_current;
	int activity;
	struct sockaddr_in dcserver;
	struct sockaddr_in dcclient;
	char buf[128];
	int master_socket;
	int loop;
	int client_socket[30];
	int max_clients=30;
	fd_set readfds;
	
	
	printf("Creating Socket...\n");
	/*
	if ((dcsocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket \n");
	}*/
	
	//initialise all clients
	for (loop=0; loop < max_clients; loop++) {
		client_socket[loop] = 0;
	}
	
	/* create the master socket and check it worked */
	if ((master_socket = socket(AF_INET,SOCK_STREAM,0))==0) {
		/* if socket failed then display error and exit */
		perror("Create master_socket");
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, 
				   (char *)&opt, sizeof(opt))<0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	
	//setup our server
	memset(&dcserver, 0, sizeof(dcserver));
	dcserver.sin_family = AF_INET;
	dcserver.sin_addr.s_addr = INADDR_ANY;
	dcserver.sin_port = htons(8000);
	
		
	
	// bind the socket to the port number 
	if (bind(master_socket, (struct sockaddr *)&dcserver, sizeof(dcserver))<0) {
		/* if bind failed then display error message and exit */
		perror("bind");
		exit(EXIT_FAILURE);
	}
	

	printf("Waiting for connections...\n");
	if (listen(master_socket, 30)<0) {
		/* if listen failed then display error and exit */
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	/*
	addrlen = sizeof(dcclient);
	printf("Accepting Connections...\n");
	
	if ((socket_current = accept(dcsocket, (struct sockaddr *) &dcclient, &addrlen)) == -1)
	{
		printf("accept\n");
			exit(1);
	}*/

	int n = 0; 
	
	while (1) 
	{
		FD_ZERO(&readfds);
		
		FD_SET(master_socket, &readfds);
		
		for (loop=0; loop<max_clients; loop++) {
			if (client_socket[loop] > 0) {
				FD_SET(client_socket[loop], &readfds);
			}
		}
		
		activity=select(max_clients+5, &readfds, NULL, NULL, NULL);
		
		if (FD_ISSET(master_socket, &readfds)) 
		{
			/* Open the new socket as 'new_socket' */
			addrlen=sizeof(dcserver);
			if ((dcsocket = accept(master_socket, (struct sockaddr *)&dcserver, &addrlen))<0)
			{
				/* if accept failed to return a socket descriptor, display error and exit */
				perror("accept");
				exit(EXIT_FAILURE);
			}
			/* inform user of socket number - used in send and receive commands */
			printf("New socket is fd %d\n",dcsocket);
			for (loop=0; loop<max_clients; loop++) 
			{
				if (client_socket[loop] == 0) 
				{
					client_socket[loop] = dcsocket;
					printf("Adding to list of sockets as %d\n", loop);
					loop = max_clients;
				}
			}
		}
		
		for (loop=0; loop<max_clients; loop++) 
		{
			if (FD_ISSET(client_socket[loop], &readfds)) 
			{
				n = recv(client_socket[loop], buf, sizeof(buf), 0);	
				if (n)
				{
					buf[n] = 0;
					char *returnString;
					returnString = processCommand(buf);
					send(client_socket[loop], returnString, strlen(returnString), 0);
					returnString = 0;
				}
			}
		}
		
			
	}
	
	
	
	/*if (recv(socket_current, buf, sizeof(buf), 0) == -1)
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
	}*/


	close(socket_current);
  // close(dcserver);
  // close(dcclient);
	
	exit(0);
}