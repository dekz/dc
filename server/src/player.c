#include "player.h"

Player* new_player()
{
  Player *p = malloc(sizeof(Player));
  
  return p;
}

Player *getPlayer(char *name)
{
  //this will play up if the player doesn't exist, will return head TODO
  //problems if there is no head either
  node *n = g_pl.head;
  for (int i = 0; i < g_pl.size; i++) 
  {
    if (!strcmp(name, n->player->name)) 
    {
      return n->player;
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
  static char* plInfo[128];
  pl = getPlayer(name);
  if (pl != 0)
  {
    pl->queryCount++;
    //attach player details to the string
    //make sure i don't need to malloc TODO
    sprintf(plInfo, "%s %s %d %d %d %d", pl->name, pl->country, pl->innings, pl->runs,pl->nOut,pl->hScore);
    return plInfo;
    
  } 
  return 0;
}