#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "../../shared/src/bool.h"

typedef struct LinkedListNode {
  void *data;
  struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
  LinkedListNode *head;
  int size;  
} LinkedList;

bool new_node(LinkedList *ll, void *data, int size);
//node *get_node(int num);
// LinkedListNode *get_node_name(char* name);
//bool linked_list_contains(Player *player);

#endif 