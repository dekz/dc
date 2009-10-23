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

bool authenticated();
int receive_message(char *buf);
int send_message(char *msg);
void auth_prompt();
void communicate();
void print_welcome_message();
void prompt(char *message, char *response, int size);
