

#include "shared.h"

#define HOST           "localhost"
#define MAX_AUTH_SIZE  20

int receive_message(char *buf);
int send_message(char *msg);
void auth_prompt();
void communicate();
void lookup_player();
void print_welcome_message();
void prompt(char *message, char *response, int size);
void socket_start();
void socket_setup();
void socket_connect();
