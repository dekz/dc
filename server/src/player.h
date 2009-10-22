#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include "../../shared/src/bool.h"


typedef struct  {
  char name[10];
  char country[3];
  int innings;
  int runs;
  int nOut;
  int hScore;
  bool isNO;
  int queryCount;
} Player;


Player* new_player();
#endif