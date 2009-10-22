#include "authentication.h"
#include "string.h"

bool authenticate(char *name, char *pw)
{
  User *u;
  if ((u = getUser(name)))
  {
    if (!strcmp(u->pw, pw))
    {
      return FALSE;
    }
  }
  return TRUE;
}

bool load_users()
{
  char *mode = "r";
  char filename[] = USERS_FILE;
  char input[128]; //buffer for input data
  char buffer[25];
  FILE* file;
  file = fopen(filename, mode);
  User *u;
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
      
      u = new_user();  
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
                strcpy(u->name, buffer);
                break;
              case 1:
                strcpy(u->pw, buffer);
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
      
      new_user_node(u);
      printf("%s\n", u->name);
      
    }
  }
  
  fclose(file);
  
  return 1;
}