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

//adding a new user to our user linked list
bool *new_user_node(user *a_user)
{
	if (a_user == NULL) return FALSE;
	
	userNode *new_node = malloc(sizeof(userNode));
	
	new_node->u = a_user;
	new_node->next = NULL;
	
	lock();
	
	userNode *current = g_ul.head;
	
	if (current == NULL)
	{
		g_ul.head = new_node;
		
	} else {
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	
	g_ul.size++;
	
	unlock();
	
	return TRUE;
}

user *new_user()
{
	user *u = malloc(sizeof(user));
	return u;
}

user *getUser(char *name)
{
	userNode *n = g_ul.head;	
	for (int i = 0; i < g_ul.size; i++) 
	{
		if (!strcmp(name, n->u->name)) 
		{
			return n->u;
		}
		else
		{
			n = n->next; //check later for NULLS TODO
		}
	}
	
}