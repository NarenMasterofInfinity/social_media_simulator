#include "classes.hpp"

#ifndef CONV_DB_H
#define CONV_DB_H
#define CONV_MAX 10

Conversation *convs[CONV_MAX];

static int j = 0;


void store_conv(Conversation *a)
{
    convs[j++] = a;
}

#endif