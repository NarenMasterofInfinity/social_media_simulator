#include "classes.h"
#include "user_methods.h"
#include "conv_db.h"
#include "text_methods.h"

#ifndef CONV_METHODS_H
#define CONV_METHODS_H

void Conversation::add_participants(User *user1, User *user2)
{
    participants[0] = user1;
    participants[1] = user2;
}

void Conversation::add_participants(Group *grp)
{
    for (int i = 0; i < count; i++)
    {
        participants[i] = grp->users[i];
    }
}

void Conversation::display_participants()
{
    cout << "|=====================================================|" << endl;
    cout << "|                   participants' details             |" << endl;
    cout << "|=====================================================|" << endl;
    for (int i = 0; i < count; i++)
    {
        User *u = participants[i];
        cout << "Username : " << u->getUsername() << endl;
    }
}

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
        if (!convs[i]->group_or_normal)
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

void Conversation::create_interface_dm()
{
    cout << "=======================================================" << endl;
    cout << "                     Direct Messages                   " << endl;
    cout << "=======================================================" << endl;
    display_participants();
    cout << "=======================================================" << endl;
    for (int i = 0; i < MAX_C; i++)
    {
        if (chats_text[i])
        {
            cout << chats_text[i]->getAuthor()->getUsername() << " : " << chats_text[i]->getContent() << endl;
        }
    }
    cout << "=======================================================" << endl;
}

void Conversation::sendText(User *owner)
{
    cout << "=========================================================" << endl;
    string content;
    cout << "Sending as " << owner->getUsername() << endl;
    cout << "Enter Text: ";
    getline(cin >> ws, content);
    cout << "=========================================================" << endl;
    chats_text[text_ptr] = new Text();
    chats_text[text_ptr]->setAuthor(new User(owner->getUsername(), owner->getPassword(),owner->getEmail()));
    chats_text[text_ptr]->setContent(content);
    text_ptr += 1;
}

#endif