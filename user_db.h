#include "classes.h"

#ifndef USER_DB_H
#define USER_DB_H

User user[USER_MAX];

static int i = 0;

void store_user(User *a)
{
    user[i++] = *a;
}

#endif