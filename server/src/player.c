#include "player.h"

void* new_player()
{
	Player *p = malloc(sizeof(Player));
	
	return p;
}
