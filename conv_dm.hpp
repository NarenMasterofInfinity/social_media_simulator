#include "user_methods.hpp"
#include "user_db.hpp"
#include "conv_methods.hpp"
#include "classes.hpp"

#ifndef CONV_DM_H
#define CONV_DM_H

void DMConversation::add_particpants(User *user1, User *user2)
{
    this->participants[0] = user1;
    this->participants[1] = user2;
}
string DMConversation::getType()
{
    return NORMAL_CONV;
}
void DMConversation::display_participants()
{
    std::cout << "|=====================================================|" << endl;
    std::cout << "|                   participants' details             |" << endl;
    std::cout << "|=====================================================|" << endl;
    for (int i = 0; i < count; i++)
    {
        User *u = participants[i];
        std::cout << "Username : " << u->getUsername() << endl;
    }
}
void DMConversation::create_interface()
{
    std::cout << "=======================================================" << endl;
    std::cout << "                     Direct Messages                   " << endl;
    std::cout << "=======================================================" << endl;
    display_participants();
    std::cout << "=======================================================" << endl;
    for (int i = 0; i < MAX_C; i++)
    {
        if (chats_msgs[i])
        {
            chats_msgs[i]->display();
        }
    }
    std::cout << "=======================================================" << endl;
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

template <class T>
void DMConversation::sendText(User *owner)
{
    T *data;
    string path;
    cout << "Sending as " << owner->getUsername() << endl;
    cout << "Enter the path of the file: ";
    cin >> path;
    bool status = Multimedia::validate<T>(path);
    if (status)
    {
        data = new T(path);
        data->setAuthor(owner);
        chats_msgs[text_ptr++] = data;
    }
}

template <>
void DMConversation::sendText<Text<String>>(User *owner)
{
    string content;
    std::cout << "Sending as " << owner->getUsername() << endl;
    std::cout << "Enter Text: ";
    getline(cin >> ws, content);
    Text<> *data = new Text<>(content);
    data->setAuthor(owner);
    chats_msgs[text_ptr++] = data;
}

template <>
void DMConversation::sendText<Text<Emoji>>(User *owner)
{
    string content;
    std::cout << "Sending as " << owner->getUsername() << endl;
    std::cout << "Enter Text: ";
    getline(cin >> ws, content);
    Text<Emoji> *data = new Text<Emoji>(content);
    data->setAuthor(owner);
    chats_msgs[text_ptr++] = data;
}
#endif
