
//user for authentication
typedef struct user {
  char name[20];
  char pw[20];
} user;

typedef struct userNode {
  user *u;
  struct userNode *next;
} userNode;

//user linked list
typedef struct UserLinkedList {
  userNode *head;
  int size;  
} UserLinkedList;

bool *new_user_node(user *a_user);
user *new_user();
user *getUser(char *name);