#include "classes.hpp"
#include "user_db.hpp"
#include "conv_db.hpp"


#ifndef USER_METHODS_H
#define USER_METHODS_H

void User::setUsername(string username)
{
    this->username = username;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPassword(string password)
{
    this->password = password;
}

string User::getEmail()
{
    return email;
}

string User::getPassword()
{
    return password;
}

string User::getUsername()
{
    return username;
}

User *User::search_user(string username)
{
    for (int j = 0; j < USER_MAX; j++)
    {
        if (user[j]->getUsername() == username)
        {
            return user[j];
        }
    }

    return nullptr;
}
Conversation *search_dm_conversations(string user1, string user2)
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

bool operator>(User user1, User user2)
{
    Conversation *c = search_dm_conversations(user1.getUsername(), user2.getUsername());
    if (true)
    {
        User *u = &user1;
        c->sendText(u);
        return true;
    }
    return false;
}

#endif
