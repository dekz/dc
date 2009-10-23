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
  FILE* file;
  file = fopen(filename, mode);
  User *u;

	if (file == NULL)
	{
		perror("fileopen");
		exit(1);
	}
	
	while (fgets(input, 128, file) != NULL) {
		if (input[0] != '#') //check for the comments
		{
			
			u = new_user();  
			//load in the user details
			sscanf(input, "%s %s", u->name, u->pw);
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
			if (inText)
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
	
	// if ( (username == 0) || (password == 0))
	// {
	// 	return 0;
	// }
	// 
	return authenticate(username, password);
}