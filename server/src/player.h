#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "bool.h"

typedef struct  {
	char name[10];
	char country[3];
	int innings;
	int runs;
	int nOut;
	int hScore;
	bool hisNo;
} Player;


void* new_player();
#endif