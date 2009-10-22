#ifndef GLOBALS_H
#define GLOBALS_H


#include <pthread.h>
#include "../../shared/src/shared.h"
#include "user.h"
#include "player.h"
#include "linked_list.h"

pthread_mutex_t mutex;

bool g_keep_running;
LinkedList g_pl;
UserLinkedList g_ul;
#endif