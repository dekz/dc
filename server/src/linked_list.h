#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "../../shared/src/bool.h"
#include "player.h"


//user for authentication
typedef struct user {
	char name[20];
	char pw[20];
} user;

typedef struct userNode {
	user *u;
	struct userNode *next;
} userNode;

//user linked list
typedef struct UserLinkedList {
	userNode *head;
	int size;	
} UserLinkedList;

//player linked list
typedef struct node {
	Player *player;
	struct node *next;
} node;

typedef struct LinkedList {
	node *head;
	int size;	
} LinkedList;


bool *new_node(Player *player);
bool *new_user_node(user *a_user);
user *new_user();
user *getUser(char *name);
//node *get_node(int num);
//node *get_node_name(char* name);
//bool linked_list_contains(Player *player);

#endif 