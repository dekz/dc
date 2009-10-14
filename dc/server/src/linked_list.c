#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"
#include "string.h"


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

node *get_node(int num)
{
	return 0;
}

node *get_node_name(char* name)
{
	return 0;	
}

bool linked_list_contains(Player *player)
{
	return 0;	
}