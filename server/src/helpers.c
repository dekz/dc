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
  char *mode = "r";
  char filename[] = DATA_FILE;
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
    
  fclose(file);
  
  return 1;
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



/*char *getCommand(char* buf)
{
  int size = strlen(buf);
  static char command[20];
  for (int i = 0; i < size; i++) {
    if (buf[i] != ' ') {
      command[i] = buf[i];
    }
    else 
    {
      return command;
    }
  }
  return 0;
}*/

char *processCommand(char* buf)
{
  //char *command = getCommand(buf); //was going to be used if there was commands like add delete
  //int size = strlen(command);
  static char *playerInfo;
  playerInfo = getPlayerInfo(buf);
  if (playerInfo != NULL)
  {
    return playerInfo;
    
  } else 
  {
    playerInfo = "No Such player\n";
    return playerInfo;
  }
  
}