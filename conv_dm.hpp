#include "user_methods.hpp"
#include "user_db.hpp"
#include "conv_methods.hpp"
#include "classes.hpp"

#ifndef CONV_DM_H
#define CONV_DM_H


void DMConversation::add_particpants(User *user1, User *user2){
    this->participants[0] = user1;
    this->participants[1] = user2;
}
string DMConversation::getType()
{
    return NORMAL_CONV;
}
void DMConversation::display_participants()
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
void DMConversation::create_interface()
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
            chats_text[i]->display();
        }
    }
    cout << "=======================================================" << endl;
}

void DMConversation::exitConvo(User *initiator)
{
    string exiter = initiator->getUsername();
    int i = 0;
    for (; i < 2; i++)
    {
        if (participants[i]->getUsername() == exiter)
        {
            last_seen[i] = time(NULL);
        }
    }
}

void DMConversation::starMessage(Message *)
{
    return;
}

void DMConversation::sendText(User *owner)
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
