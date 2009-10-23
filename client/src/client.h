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

#define HOST           "localhost"
#define MAX_AUTH_SIZE  20

int send_message(int sockfd, char *msg);
int receive_message(int sockfd, char *buf);
void print_welcome_message(int socket, bool should_print);