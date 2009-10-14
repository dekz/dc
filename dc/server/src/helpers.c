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
	char *mode = "r";
	char filename[] = "BATTING.TXT";
	char input[128]; //buffer for input data
	char buffer[25];
	FILE* file;
	file = fopen(filename, mode);
	Player *pl;
	int index = 0;
	int length = 0;
	int partialLine = 0;
	int partIndex = 0;
	int inText = FALSE;
	char current = (char)0x00;
	
	if (file == NULL)
	{
		perror("fileopen");
		exit(1);
	}

	while (fgets(input, 128, file) != NULL) {
		if (input[0] != '#') //check for the comments
		{
			
			pl = new_player();	
			partialLine = 0;
			partIndex = 0;
			memset(buffer, 0, 25);
			length = strlen(input);
			
			for (index = 0; index < length; index++) {
				current = input[index];
				//check whitespaces
				if (current == ' ' || current == '\t' || current == '\n' || current == 'r') {
					
					if (inText == TRUE)
					{
						switch (partialLine) {
							case 0:
								strcpy(pl->name, buffer);
								break;
							case 1:
								strcpy(pl->country, buffer);
								break;
							case 2:
								pl->innings = atoi(buffer);
								break;
							case 3:
								pl->runs = atoi(buffer);
								break;
							case 4:
								pl->nOut = atoi(buffer);
								break;
							case 5:
								pl->hScore = atoi(buffer);
								break;
							case 6:
								pl->isNO = (buffer[0] == 'T');
								break;
							default:
								break;
						}
						
						partialLine++;
						partIndex = 0;
						memset(buffer, 0,25);
						inText = FALSE;
					}
				}
				else {
					buffer[partIndex++] = current;
					inText = TRUE;
				}

			}
			
			new_node(pl);
			printf("%s\n", pl->name);
			
		}
	}
	
	/*while(fscanf(fp, "%s %s %d %d %d %d %d", pl->name, pl->country, pl->innings, pl->runs, pl->nOut, pl->hScore, pl->hisNo) != EOF)
	{
		//malloc and pass pl to linked list load
		new_node(pl);
		pl = new_player(); //check this
		printf("%s",pl->name);	
	}*/
	
	
	//printf("%s",g_pl.head->player->name);
	
	fclose(file);
	
	return 1;
}

bool load_users()
{
	return 1;
}