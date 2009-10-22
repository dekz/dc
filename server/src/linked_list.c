#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"
#include "string.h"

//adding a new batting player to the linked list
bool *new_node(Player *player)
{
  if (player == NULL) return FALSE;
  
  node *new_node = malloc(sizeof(player));
  
  new_node->player = player;
  new_node->next = NULL;
  
  lock();
  
  node *current = g_pl.head;
  
  if (current == NULL)
  {
    g_pl.head = new_node;
    
  } else {
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
  
  g_pl.size++;
  
  unlock();
  
  return TRUE;
}