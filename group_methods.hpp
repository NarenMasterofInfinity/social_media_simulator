#include "classes.hpp"
#include "user_db.hpp"

#ifndef GROUP_METHODS_H
#define GROUP_METHODS_H
void GroupConversation::add_participants(int count)
{
    cout << "|=====================================================|" << endl;
    cout << "|                   Add participants                  |" << endl;
    cout << "|=====================================================|" << endl;
    string usernames[count];
    int ptr = 0;
    if (creator)
    {
        ptr++;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "Enter group member " << i + 1 << "'s username :  ";
        cin >> usernames[i];
        User *u = User::search_user(usernames[i]);
        if (u == nullptr)
        {
            cout << "User with " << usernames[i] << " doesn't exist" << endl;
        }
        else
        {
            this->participants[ptr++] = User::search_user(usernames[i]);
        }
    }
    cout << "========================================================" << endl;
}

void GroupConversation::create_interface()
{
    cout << "=======================================================" << endl;
    cout << "                  Group " << group_name << "               " << endl;
    cout << "=======================================================" << endl;
    display_participants();
    for (int i = 0; i < MAX_C; i++)
    {
        if (chats_text[i])
        {
            chats_text[i]->display();
        }
    }
}

void GroupConversation::sendMessage(Message *msg)
{
    if (msg->getType() == TEXT_MSG)
    {
        chats_text[text_ptr++] = msg;
    }
}

void GroupConversation::display_participants()
{
    cout << "|=====================================================|" << endl;
    cout << "|              Participants' details                  |" << endl;
    cout << "|=====================================================|" << endl;
    for (int i = 0; i < GROUP_MAX; i++)
    {
        if (participants[i])
        {
            cout << i + 1 << " : " << participants[i]->getUsername() << endl;
        }
    }
    cout << "========================================================" << endl;
}


string GroupConversation::getType()
{
    return GROUP_CONV;
}
#endif
