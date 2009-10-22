#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "shared.h"
#include "helpers.h"

#define HOST "localhost"

int sendmessage(int sockfd, char *msg);
int receivemessage(int sockfd, char *buf);