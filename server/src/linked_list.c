#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "shared.h"
#include "helpers.h"
#include "string.h"

//adding a new batting player to the linked list
bool new_node(LinkedList *ll, void *data, int size)
{
  if (data == NULL) return FALSE;
    
  LinkedListNode *new_node = malloc(size);
  
  new_node->data = data;
  new_node->next = NULL;
  
  lock();
  
  LinkedListNode *current = ll->head;
  
  if (current == NULL)
  {
    ll->head = new_node;
    
  } else {
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
  
  ll->size++;
  
  unlock();
  
  return TRUE;
}