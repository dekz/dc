#include "shared.h"

bool load_users();
bool authenticate(char *name, char *pw);
bool strip_auth(char *buf);