#ifndef HELPERS_H
#define HELPERS_H
#define USERS_FILE "data/USERS.txt"
#define DATA_FILE  "data/BATTING.txt"

//#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "player.h"

void welcome_message();
void lock();
void unlock();
char *getCommand(char* buf);
char *processCommand(char* buf);
#endif