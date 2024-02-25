#include "classes.hpp"
#include "user_db.hpp"

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

bool operator>(User user1, User user2)
{
    Conversation *c = Conversation ::search_dm_conversations(user1, user2);
    if (true)
    {
        User *u = &user1;
        c->sendText(u);
        return true;
    }
    return false;
}
#endif
