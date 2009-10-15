#include "client.h"
#define HOST "localhost"

int main()
{
	
	char hostname[100];
	char buf[100];
	char *message = "MESSAGE FROM CLIENT";
	int dcsocket;
	struct sockaddr_in dcserver;
	struct hostent *hp;
	
	strcpy(hostname, HOST);
	printf("Attempting to get hostname...\n");
	if ((hp = gethostbyname(HOST)) == 0)
	{
		perror("get host name");
		exit(1);
	}
	
	printf("Got hostname.\n");
	
	/*
	 * copy the network address part of the structure to the 
	 * sockaddr_in structure which is passed to connect() 
	 */
	memcpy(&dcserver.sin_addr, hp->h_addr_list[0], hp->h_length);
	printf("Setting up server struct...\n");
	dcserver.sin_family = AF_INET;
//	dcserver.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	dcserver.sin_port = htons(7000);
	printf("Server struct setup...\n");
	
	if ((dcsocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	
	if (connect(dcsocket, (struct sockaddr *)&dcserver, sizeof(dcserver)) == -1)
	{
		perror("connect");
		exit(1);
	}
	
	if (send(dcsocket, message, strlen(message), 0) == -1)
	{
		perror("send");
		exit(1);
	}
	
	if (recv(dcsocket, buf, sizeof(buf), 0) == -1)
	{
		perror("recv");
		exit(1);
	}
	printf("%s\n", buf);
	
	
	close(dcsocket);
	close(dcserver);


	exit(0);
}

int sendmessage(int sockfd, char *msg)
{
	
	if (send(sockfd, msg, strlen(msg), 0) == -1)
	{
		perror("send");
		exit(1);
	}
}

int receivemessage(int sockfd, char *buf)
{
	if (recv(sockfd, buf, sizeof(buf), 0) == -1)
	{
		perror("recv");
		exit(1);
	}
	
	printf("%s\n", buf);
	
}