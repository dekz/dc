#include "helpers.h"

void welcome_message()
{
	
}

void lock() 
{
    pthread_mutex_lock(&mutex);
}

void unlock() 
{
    pthread_mutex_unlock(&mutex);
}

bool load_data()
{
	
	FILE *fp;
	char *mode = "w+";
	char filename[] = "BATTING.TXT";
	fp = fopen(filename, mode);
	
	if (fp == NULL)
	{
		perror("fileopen");
		exit(1);
	}

	Player *pl;
	pl = new_player();	
	while(fscanf(fp, "%s %s %d %d %d %d %d", pl->name, pl->country, pl->innings, pl->runs, pl->nOut, pl->hScore, pl->hisNo) != EOF)
	{
		//malloc and pass pl to linked list load
		new_node(pl);
		pl = new_player(); //check this
	}
	
//	printf("%s",g_pl.head->player->name);
	
	fclose(fp);
	
	return 1;
}

bool load_users()
{
	return 1;
}