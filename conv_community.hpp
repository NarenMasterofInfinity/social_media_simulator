#include "user_methods.hpp"
#include "conv_methods.hpp"
#include "user_db.hpp"
#include "classes.hpp"

#ifndef CONV_COMMUNITY_H
#define CONV_COMMUNITY_H
string CommunityConversation::getCommunityName()
{
    return community_name;
}
void CommunityConversation::setCommunityName(string username, string name)
{
    if (authenticate(username))
    {
        this->community_name = name;
    }
    else
    {
        cout << "You lack necessary permissions :(";
    }
}
string CommunityConversation::getCommunityDescription()
{
    return community_description;
}
void CommunityConversation::setCommunityDescription(string username, string desc)
{
    if (authenticate(username))
    {
        this->community_description = desc;
    }
    else
    {
        cout << "You lack the necessary permissions :(";
    }
}

bool CommunityConversation::authenticate(string username)
{
    for (int i = 0; i < GROUP_MAX; i++)
    {
        if (!admins[i])
        {
            return false;
        }
        else
        {
            if (admins[i]->getUsername() == username)
            {
                return true;
            }
        }
    }
    return false;
}

void CommunityConversation::display_participants()
{
    cout << "|=====================================================|" << endl;
    cout << "|                   participants' details             |" << endl;
    cout << "|=====================================================|" << endl;
    cout << "                           Admins                      " << endl;
    for (int i = 0; i < GROUP_MAX; i++)
    {
        if (admins[i])
        {
            cout << i + 1 << " : " << admins[i]->getUsername() << endl;
        }
    }
    cout << "--------------------------------------------------------" << endl;
    cout << "                        Normal Members                  " << endl;
    for (int i = 0, h = 0; i < p_ptr; i++)
    {
        if (participants[i])
        {
            bool flag = true;
            for (int j = 0; j < GROUP_MAX; j++)
            {
                if (admins[j])
                {
                    if (admins[j] == participants[i])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag)
            {
                if(participants[i]->getUsername() == "") continue;
                cout << h + 1 << " : " << participants[i]->getUsername() << endl;
                h++;
            }
        }
    }
    cout << "----------------------------------------------------------" << endl;
}

void CommunityConversation::sendMessage(Message *msg)
{
    User *author = msg->getAuthor();
    if (authenticate(author->getUsername()))
    {
        chats_text[text_ptr++] = msg;
    }
    else
    {
        cout << "Sorry! Only admins can post in this community" << endl;
    }
}

void CommunityConversation::create_interface()
{
    cout << community_name << endl;
    cout << "Description : " << community_description << endl;
    display_participants();
    for (int i = 0; i < MAX_C; i++)
    {
        if (chats_text[i])
        {
            chats_text[i]->display();
        }
    }
}

void RequestBasedCommunity::addMembers(string username, int count)
{
    if (!authenticate(username))
    {
        cout << "You don't have permission to add members!" << endl;
        return;
    }
    cout << "|=====================================================|" << endl;
    cout << "|                   Add participants                  |" << endl;
    cout << "|=====================================================|" << endl;
    string usernames[count];
    int ptr = 0;
    if (creator)
    {
        p_ptr++;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "Enter Community member " << i + 1 << "'s username :  ";
        cin >> usernames[i];
        User *u = User::search_user(usernames[i]);
        if (u == nullptr)
        {
            cout << "User with " << usernames[i] << " doesn't exist" << endl;
        }
        else
        {
            this->participants[p_ptr++] = User::search_user(usernames[i]);
        }
    }
    cout << "========================================================" << endl;
}

void RequestBasedCommunity ::issueRequest(User *u)
{
    request_queue[request_ptr++] = u;
    cout << "Request sent to the admin." << endl;
}

void RequestBasedCommunity ::acceptRequest(User *admin)
{
    cout << "Here is the status of the request queue" << endl;
    for (int i = 0; i < request_ptr; i++)
    {
        char choice;
        cout << "Request " << i + 1<<" " << request_queue[i]->getUsername() << endl;
        cout << "Do you wish to add " << request_queue[i]->getUsername() << " ? (y/n) ";
        cin >> choice;
        if (choice == 'y')
        {
            participants[p_ptr++] = request_queue[i];
        }
    }
}

string CommunityConversation::getType()
{
    return COMMUNITY_CONV;
}

void FreeJoinCommunity :: addMembers(int count){
    cout << "|=====================================================|" << endl;
    cout << "|                   Add participants                  |" << endl;
    cout << "|=====================================================|" << endl;
    string usernames[count];
    int ptr = 0;
    if (creator)
    {
        p_ptr++;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "Enter Community member " << i + 1 << "'s username :  ";
        cin >> usernames[i];
        User *u = User::search_user(usernames[i]);
        if (u == nullptr)
        {
            cout << "User with " << usernames[i] << " doesn't exist" << endl;
        }
        else
        {
            this->participants[p_ptr++] = User::search_user(usernames[i]);
        }
    }
    cout << "========================================================" << endl;
}

void FreeJoinCommunity :: joinCommunity(User* u){
    this->participants[p_ptr++] = u;
}

#endif