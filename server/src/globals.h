#include <pthread.h>
#include "linked_list.h"
#include "players.h"

pthread_mutex_t mutex;

bool g_keep_running;
LinkedList _pl;