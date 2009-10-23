#include <string.h>
#include "player.h"
#include "linked_list.h"
#include "shared.h"

bool new_player_node(Player *pl)
{
  return new_node(&g_playerList, (void *)pl, sizeof(pl));
}

Player* new_player()
{
  Player *p = malloc(sizeof(Player));
  return p;
}

Player *getPlayer(char *name)
{
  //this will play up if the player doesn't exist, will return head TODO
  //problems if there is no head either
  
  LinkedListNode *n = g_playerList.head;
  for (int i = 0; i < g_playerList.size; i++) 
  {
    Player *p = n->data;
    
    if (!strcmp(name, p->name)) 
    {
      return p;
    }
    else
    {
      n = n->next; //check later for NULLS TODO
    }
  }
  return 0;
}

char *getPlayerInfo(char *name)
{
  Player* pl;
  static char plInfo[MAX_MESSAGE_SIZE];
  pl = getPlayer(name);
  if (pl != 0)
  {
    pl->queryCount++;
    //attach player details to the string
    //make sure i don't need to malloc TODO
    snprintf(plInfo, MAX_MESSAGE_SIZE, "0\t%s\t%s\t%d\t%d\t%d\t%d\t%d", pl->name, pl->country, pl->innings, pl->runs,pl->nOut,pl->hScore, pl->queryCount);
    return plInfo;
    
  } 
  return 0;
}