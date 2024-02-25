#include "classes.hpp"
#include "user_methods.hpp"
#include "conv_db.hpp"
#include "text_methods.hpp"

#ifndef CONV_METHODS_H
#define CONV_METHODS_H

Conversation *Conversation::search_dm_conversations(User user1, User user2)
{
    return Conversation::search_dm_conversations(user1.getUsername(), user2.getUsername());
}
Conversation *Conversation::search_dm_conversations(User *user1, User *user2)
{
    return Conversation::search_dm_conversations(*user1, *user2);
}

Conversation *Conversation::search_dm_conversations(string user1, string user2)
{
    for (int i = 0; i < CONV_MAX; i++)
    {
        if (!convs[i])
            return nullptr;
        if (convs[i]->getType() == NORMAL_CONV)
        { // if it is a normal conversation
            User *u[2] = {convs[i]->participants[0], convs[i]->participants[1]};
            for (int j = 0; j < 2; j++)
            {
                if (u[j])
                {
                    if (u[j]->getUsername() != user1 && u[j]->getUsername() != user2)
                    {
                        return nullptr;
                    }
                }
                else
                {
                    return nullptr;
                }
            }
            return convs[i];
        }
    }
    return nullptr;
}




#endif