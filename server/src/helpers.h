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
bool load_data();
Player *getPlayer(char *name);
char *getPlayerInfo(char *name);
char *getCommand(char* buf);
char *processCommand(char* buf);
#endif