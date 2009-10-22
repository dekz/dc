#ifndef HELPERS_H
#define HELPERS_H

//#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#include "player.h"

void welcome_message();
void lock();
void unlock();
char *getCommand(char* buf);
char *processCommand(char* buf);
#endif