#include "server.h"
#include "data.h"
#include "authentication.h"

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
	setup_socket();
	int opt=TRUE;
	int dcsocket;
	socklen_t addrlen;
	int socket_current;
	int activity;
	struct sockaddr_in dcserver;
	char buf[128];
	int master_socket;
	int loop;
	int client_socket[30];
	int max_clients=30;
	fd_set readfds;
	char welcomeString[] = "Welcome to the Cricket Scores\n\t\tSincerely, the Server";
	
	printf("Creating Socket...\n");

	
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
	dcserver.sin_port = PORT;
	
    
	
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
					send(client_socket[loop], welcomeString, strlen(welcomeString)+1, 0);
					printf("Adding to list of sockets as %d\n", loop);
					loop = max_clients;
				}
			}
		}
		
		
		/*
	Client message loop
		iterate over the array of connections
		check if anything is received, this should be authentication
			if authentication passed then attempt to receive command
				process command
				return string
		close connection
		 */
		
		for (loop=0; loop<max_clients; loop++) 
		{
			if (FD_ISSET(client_socket[loop], &readfds)) 
			{
				//buffer should be in the form of "user\tpassword\tquery"
				char username[20];
				char password[20];
				char query[20];
				memset(buf, 0, strlen(buf));
				n = read(client_socket[loop], buf, sizeof(buf));  //login credentials and query
				
				if (n)
				{
					//load in the details from the buffer string
					sscanf(buf, "%s %s %s", username, password, query);
				}
				
				//authenticate the user
				if (authenticate(username, password))
				{
					//once authenticated, send the informtion
					char *returnString;
					returnString = processCommand(query);
					send(client_socket[loop], returnString, strlen(returnString) +1, 0);
				} else
				{
					send(client_socket[loop], "2", 2, 0);
				}
				
				printf("Closing socket\n ");
				close(client_socket[loop]);	
				client_socket[loop] = 0;
				//close connection
				//remove connection from client_socket
				//set to null
				//shuffle the client_socket
				//lower count of max_clients?
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
	
	exit(0);
}