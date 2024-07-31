#include "user_methods.hpp"
#include "conv_methods.hpp"
#include "user_db.hpp"
#include "classes.hpp"
#include <unistd.h>

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
    for (int i = 0; i < admins.size(); i++)
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
    for (int i = 0; i < admins.size(); i++)
    {
        if (admins[i])
        {
            cout << i + 1 << " : " << admins[i]->getUsername() << endl;
        }
    }
    cout << "--------------------------------------------------------" << endl;
    cout << "                        Normal Members                  " << endl;
    for (int i = 0, h = 0; i < participants.size(); i++)
    {
        if (participants[i])
        {
            bool flag = true;
            for (int j = 0; j < admins.size(); j++)
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
                if (participants[i]->getUsername() == "")
                    continue;
                cout << h + 1 << " : " << participants[i]->getUsername() << endl;
                h++;
            }
        }
    }
    cout << "----------------------------------------------------------" << endl;
}

void CommunityConversation::sendMessage(Message *msg)
{
    sleep(1);
    User *author = msg->getAuthor();
    if (authenticate(author->getUsername()))
    {
        chats_msgs.root = chats_msgs.insert_node(chats_msgs.root, msg);
        sendNotifications(author->getUsername());
    }
    else
    {
        cout << "Sorry! Only admins can post in this community" << endl;
    }
}
bool msgsortfn1(Message *m1, Message *m2)
{
    return m1->created_at < m2->created_at;
}

void CommunityConversation::create_interface()
{
    cout << "=======================================================" << endl;
    cout << "            " << community_name << endl;
    cout << "=======================================================" << endl;

    cout << "Description : " << community_description << endl
         << endl;
    display_participants();
    int choice;
    
    do
    {
        cout << "1. View community polls\n2. View messages\n3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            displayPolls();
        }
        break;
        case 2:
        {
            list<Message *> allmsgs;
            chats_msgs.getmsgs(chats_msgs.root, allmsgs);
            allmsgs.sort(msgsortfn1);
            for (auto i : allmsgs)
            {
                i->display();
            }
        }
        break;
        case 3:
        {
            cout << "Exiting.." << endl;
            return;
        }
        break;
        default:
        {
            cout << "Invalid choice" << endl;
        }
        break;

        }
    } while (choice != 3);
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
    request_queue.push(u);
    cout << "Request sent to the admin." << endl;
}

void RequestBasedCommunity ::acceptRequest(User *admin)
{

    cout << "Here is the status of the request queue" << endl;
    int n = request_queue.size();
    if (n == 0)
    {
        cout << "No requests present" << endl;
        return;
    }
    int i = 0;
    while (i < n)
    {
        char choice;
        User *u = request_queue.front();
        cout << "Request " << ++i << " " << u->getUsername() << endl;
        cout << "Do you wish to add " << u->getUsername() << " ? (y/n) ";
        cin >> choice;
        if (choice == 'y')
        {
            participants.push_back(u);
            string content = "You have been added to the community " + community_name + ". Welcome aboard!";
            admin->sendNotification(u, this, content);
            request_queue.pop();
        }
        else
        {
            request_queue.push(u);
            request_queue.pop();
        }
    }
}

char CommunityConversation::getType()
{
    return COMMUNITY_CONV;
}

void FreeJoinCommunity ::addMembers(int count)
{
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

void FreeJoinCommunity ::joinCommunity(User *u)
{
    if (u->getUsername() == this->creator->getUsername())
    {
        return;
    }
    this->participants.push_back(u);
    cout << "Successfully joined " << this->getCommunityName() << " Community :) " << endl;
}

void CommunityConversation::createPoll()
{
    Poll *poll = new Poll;
    string question, title;
    cout << "Enter the title of the poll : ";
    getline(cin >> ws, title);
    poll->setTitle(title);
    cout << "Enter question: ";
    getline(cin >> ws, question);
    poll->setQuestion(question);
    int n;
    cout << "Enter the number of options: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string option;
        cout << "Enter the option "<< i+1 << ": ";
        getline(cin >> ws, option);
        poll->addOption(option);
    }
    addPoll(poll);
    cout << "Poll added successfully" << endl;
}
void CommunityConversation::displayPolls()
{
    int i = 0;
    cout << "Here are the avaialble polls" << endl;
    if (pollsForThisCommunity.size() == 0)
    {
        cout << "No polls available" << endl;
        return;
    }
    for (auto &p : pollsForThisCommunity)
    {
        cout << ++i << " . " << p->getTitle() << endl;
    }
    int choice;
    cout << "Enter a choice (0 to exit): ";
    cin >> choice;
    if (choice == 0)
    {
        return;
    }
    pollsForThisCommunity[choice - 1]->display();
    cout << "What do you wish to vote for? (0 to exit): ";
    int choice1;
    cin >> choice1;
    if (choice1 == 0)
    {
        return;
    }
    pollsForThisCommunity[choice - 1]->vote(choice1);
    pollsForThisCommunity[choice - 1]->showResults();
}

#endif