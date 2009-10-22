#ifndef GLOBALS_H
#define GLOBALS_H

#define USERS_FILE "data/USERS.txt"
#define DATA_FILE  "data/BATTING.txt"

#include <pthread.h>
#include "../../shared/src/bool.h"
#include "user.h"
#include "player.h"
#include "linked_list.h"

pthread_mutex_t mutex;

bool g_keep_running;
LinkedList g_pl;
UserLinkedList g_ul;
#endif