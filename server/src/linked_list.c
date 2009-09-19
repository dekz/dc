#include "linked_list.h"


bool *new_node(Player *player)
{
	if (player == NULL) return FALSE;
	
	node *new_node = malloc(sizeof(player));
	
	new_node->player = player;
	new_node->next = NULL;
	
	lock();
	
	node *current = _pl->head;
	
	if (current == NULL)
	{
		_pl.head = new_node;
	} else {
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	
	_pl.size++;
	
	unlock();
	
	return TRUE;
}

node *get_node(int num)
{
	
}

node *get_node(char* name)
{
	
}

bool linked_list_contains(Player *player)
{
	
}