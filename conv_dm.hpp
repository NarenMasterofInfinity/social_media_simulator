#include "user_methods.hpp"
#include "user_db.hpp"
#include "conv_methods.hpp"
#include "classes.hpp"
#include <unistd.h>

#ifndef CONV_DM_H
#define CONV_DM_H

void DMConversation::add_particpants(User *user1, User *user2)
{
    participants.push_back(user1);
    participants.push_back(user2);
}
char DMConversation::getType()
{
    return NORMAL_CONV;
}
void DMConversation::display_participants()
{
    std::cout << "|=====================================================|" << endl;
    std::cout << "|                   participants' details             |" << endl;
    std::cout << "|=====================================================|" << endl;
    for (auto u : participants)
    {
        std::cout << "Username : " << u->getUsername() << endl;
    }
}
bool msgsortfn(Message *m1, Message *m2){
    return m1->created_at < m2->created_at;
}
void DMConversation::create_interface()
{
    std::cout << "=======================================================" << endl;
    std::cout << "                     Direct Messages                   " << endl;
    std::cout << "=======================================================" << endl;
    display_participants();
    std::cout << "=======================================================" << endl;
   // chats_msgs.inorder(chats_msgs.root);
    list<Message *> allmsgs;
    chats_msgs.getmsgs(chats_msgs.root, allmsgs);
    allmsgs.sort(msgsortfn);
    for(auto i : allmsgs){
        i->display();
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
        sleep(1);
        data = new T(path);
        data->setAuthor(owner);
        chats_msgs.insert_node(chats_msgs.root, data);
    }
}

template <>
void DMConversation::sendText<Text<String>>(User *owner)
{

    string content;
    std::cout << "Sending as " << owner->getUsername() << endl;
    std::cout << "Enter Text: ";
    getline(cin >> ws, content);
    sleep(1);
    Text<> *data = new Text<>(content);
    data->setAuthor(owner);
    chats_msgs.insert_node(chats_msgs.root, data);
}

template <>
void DMConversation::sendText<Text<Emoji>>(User *owner)
{

    string content;
    std::cout << "Sending as " << owner->getUsername() << endl;
    std::cout << "Enter Text: ";
    getline(cin >> ws, content);
    sleep(1);
    Text<Emoji> *data = new Text<Emoji>(content);
    data->setAuthor(owner);
    chats_msgs.insert_node(chats_msgs.root, data);
}

#endif
