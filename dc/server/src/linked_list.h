#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "player.h"



typedef struct node {
	Player *player;
	struct node *next;
} node;

typedef struct LinkedList {
	node *head;
	int size;	
} LinkedList;

bool *new_node();
node *get_node(int num);
node *get_node_name(char* name);
bool linked_list_contains(Player *player);

#endif 