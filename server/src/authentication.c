#include "authentication.h"
#include "string.h"

bool authenticate(char *name, char *pw)
{
  User *u;
  if ((u = getUser(name)))
  {
    if (!strcmp(u->pw, pw))
    {
      return TRUE;
    }
  }
  return FALSE;
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


bool strip_auth(char *buf)
{
	char username[20];
	char password[20];
	int length = strlen(buf);
	int inText = FALSE;
	char temp[length];
	char current = (char)0x00;
	int part = 0;
	int index = 0;
	buf[length+1] = '\r';
	
	for (int i = 0; i < length; i++) 
	{
		current = buf[i];
		if (current == '\t' || current == '\n' || current == '\r') 
		{
			if (inText = TRUE)
			{
				//we've reached the end of either the pw or the u/n
				switch (part) 
				{
					case 0:
						strcpy(username, temp);
						break;
					case 1:
						strcpy(password, temp);
						break;
					default:
						break;
				}
				part++;
				index = 0;
				memset(temp, 0, length);
				inText = FALSE;
			}
		} else 
		{
			temp[index++] = current;
			inText = TRUE;
		}
	}
	//TODO FIX
	strcpy(password, temp);
	
	if ( (username == 0) || (password == 0))
	{
		return 0;
	}
	
	return authenticate(username, password);
}