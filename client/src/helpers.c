#include <stdio.h>
#include <string.h>
#include "helpers.h"

void welcome_message()
{
  printf("Welcome to DC client.\n");
}

// removes new line from the end of the a string
int chomp(char *string)
{
  int length = strlen(string) - 1;
  
  if(length >= 0 && string[length] == '\n')
    string[length] = '\0';
    
  return length;
}

void debug(char *message)
{
  if(DEBUG == 1)
  {
    puts(message);
  }
}