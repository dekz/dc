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

