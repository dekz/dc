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



*/

int main()
{
	load_data();
	load_users();
	
	int socket_desc;
	/*If acting as a master socket, it must be bound to a port number so that clients can know where to "find" 
	the socket and connect to it. */
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in address;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(7000);
	
	bind(socket_desc,(struct sockaddr *)&address,sizeof(address));
		
	listen(socket_desc,30); //ammount of connections
	printf("trying to run\n");
	
	int addrlen;
	addrlen = sizeof(struct sockaddr_in);
	int new_socket;
	new_socket = accept(socket_desc, (struct sockaddr *)&address, &addrlen);
  	if (new_socket<0)
		printf("Accepting Connections\n");
	
	printf("New socket is %d\n",new_socket);
	
	int bufsize=1024;        /* a 1K buffer */
	char *buffer=malloc(bufsize);

	recv(new_socket,buffer,bufsize,0);
	
	if (recv > 0)
	{
		printf("recieved something?\n");
	}
	
	
	sleep(20);
	
	close(socket_desc);
	
	exit(0);
}