#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "globals.h"
#include "helpers.h"

int sendmessage(int sockfd, char *msg);
int receivemessage(int sockfd, char *buf);