#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "threads.h"

//adding a new user to our user linked list
bool new_user_node(User *user)
{
  return new_node(&g_userList, (void *)user, sizeof(user));
}

User *new_user()
{
  User *u = malloc(sizeof(User));
  return u;
}

User *getUser(char *name)
{
  LinkedListNode *n = g_userList.head;  
  for (int i = 0; i < g_userList.size; i++) 
  {
    User *u = n->data;
    
    
    if (!strcmp(name, u->name)) 
    {
      return u;
    }
    else
    {
      n = n->next; //check later for NULLS TODO
    }
  }
  return NULL;
}