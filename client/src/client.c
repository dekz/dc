#include "client.h"

#define HOST "Calvin"

int main()
{
	
	char hostname[100];
	char buf[100];
	char *message = "MESSAGE FROM CLIENT";
	int dcsocket;
	struct sockaddr_in dcclient;
	struct sockaddr_in dcserver;
	struct hostent *hp;
	
	strcpy(hostname, HOST);
	
	if ((hp = gethostbyname(hostname)) == 0)
	{
		perror("get host name");
		exit(1);
	}
	
	memset(&dcserver, 0, sizeof(dcserver));
	dcserver.sin_family = AF_INET;
	printf("%d\n", dcserver.sin_family = AF_INET);
	dcserver.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	printf("%d\n", dcserver.sin_addr.s_addr);
	dcserver.sin_port = htons(7000);
	
	if (connect(dcsocket, (struct sockaddr *)  &dcserver, sizeof(dcserver)) == -1)
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
	printf("%s", buf);
	
	close(dcsocket);
	close(dcclient);
	close(dcserver);


	exit(0);
}