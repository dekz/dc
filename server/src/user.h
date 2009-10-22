#ifndef USER_H
#define USER_H
#define USER_STRINGS_LENGTH 20

#include "../../shared/src/bool.h"

//user for authentication
typedef struct User {
  char name[USER_STRINGS_LENGTH];
  char pw[USER_STRINGS_LENGTH];
} User;


bool new_user_node(User *user);
User *new_user();
User *getUser(char *name);

// needs to be included after definition of UserLinkedList (until this is abstracted to a generic linked list)
#include "shared.h"
#endif /* end of include guard: USER_H */