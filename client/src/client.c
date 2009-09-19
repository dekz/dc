#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "client.h"
#include "helpers.h"

int main()
{
	establish_connection();
	exit(0);
}