#include "classes.hpp"
#include "user_methods.hpp"
#include "conv_db.hpp"
#include "text_methods.hpp"

#ifndef CONV_METHODS_H
#define CONV_METHODS_H

Conversation *search_dm_conversations(User user1, User user2)
{
    return search_dm_conversations(user1.getUsername(), user2.getUsername());
}
Conversation *search_dm_conversations(User *user1, User *user2)
{
    return search_dm_conversations(*user1, *user2);
}






#endif