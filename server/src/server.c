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
	
	int socket_desc;
	int reader;
	char buf[100];
	char data[10] = "TEST LOL";
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0); //TCP
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

	do {   /* Read from client until it's closed the connection. */
	            /* Prepare read buffer and read. */
	            bzero(buf, sizeof(buf));
	            if ((reader = read(socket_desc, buf, 100)) < 0)
	               printf("Reading stream message\n");

	            if (reader == 0)   /* Client has closed the connection */
	               printf("Ending connection\n");
	            else
	               printf("S: %s\n", buf);

	            /* Write back to client. */
	            if (write(socket_desc, data, sizeof(data)) < 0)
	               printf("Writing on stream socket\n");

	         } while (reader != 0);

	sleep(20);
	
	close(socket_desc);
	
	exit(0);
}