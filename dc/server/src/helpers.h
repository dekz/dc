#ifndef HELPERS_H
#define HELPERS_H
//#include "linked_list.h"
#include <stdio.h>
#include "globals.h"
#include "player.h"



void welcome_message();
void lock();
void unlock();
bool load_data();
bool load_users();
Player *getPlayer(char *name);
char *getPlayerInfo(char *name);
bool *authenticate(char *name, char *pw);
#endif