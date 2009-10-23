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

char *getCommand(char* buf)
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
}

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
    playerInfo = "1";
    return playerInfo;
  }
  
}