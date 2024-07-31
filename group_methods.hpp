#include "classes.hpp"
#include "user_db.hpp"
#include "user_methods.hpp"

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
            participants.push_back(User::search_user(usernames[i]));
        }
    }
    cout << "========================================================" << endl;
}
void GroupConversation::joinGroup(User *member)
{
    participants.push_back(member);
}
bool msgsortfn2(Message *m1, Message *m2)
{
    return m1->created_at < m2->created_at;
}
void GroupConversation::create_interface()
{
    cout << "==================================================================" << endl;
    cout << "                  Group " << group_name << "           " << endl;
    cout << "==================================================================" << endl;
    display_participants();
    list<Message *> allmsgs;
    chats_msgs.getmsgs(chats_msgs.root, allmsgs);
    allmsgs.sort(msgsortfn2);
    for (auto i : allmsgs)
    {
        i->display();
    }
    // for (int i = 0; i < MAX_C; i++)
    // {
    //     if (chats_text[i])
    //     {
    //         chats_text[i]->display();
    //     }
    // }
}

void GroupConversation::setGroupName(string gname)
{
    group_name = gname;
}

string GroupConversation::getGroupName()
{
    return this->group_name;
}

void GroupConversation::addMembers(User *admin)
{
    vector<User> theirfriends = findfriends(admin);
    int i = 0;
    for (User u : theirfriends)
    {
        cout << ++i << " . " << u.getUsername() << endl;
    }
    vector<int> choices(theirfriends.size(), 0);
    cout << "Add friends' numbers (0 to exit or stop) : " << endl;
    int innerchoice;
    do
    {
        cout << ": ";
        cin >> innerchoice;
        if (choices[innerchoice - 1] == 1)
        {
            cout << "Already added" << endl;
        }
        else if (innerchoice != 0 && innerchoice <= theirfriends.size())
        {
            User *toadd = new User(theirfriends[innerchoice - 1]);
            participants.push_back(toadd);
            // joinGroup(&theirfriends[innerchoice - 1]);
            choices[innerchoice - 1] = 1;
            cout << "Successfully added " << theirfriends[innerchoice - 1].getUsername() << endl;
        }

    } while (innerchoice != 0 && innerchoice <= theirfriends.size());
}

void GroupConversation::sendMessage(Message *msg)
{
    chats_msgs.root = chats_msgs.insert_node(chats_msgs.root, msg);
    sendNotifications((msg->getAuthor())->getUsername());
}

void GroupConversation::display_participants()
{
    cout << "|=====================================================|" << endl;
    cout << "|              Participants' details                  |" << endl;
    cout << "|=====================================================|" << endl;

    for (int pp = 0; pp < participants.size(); pp++)
    {
        User *u = participants[pp];
        //  cout << participants.size() << " " << participants.max_size() << endl;
        if (participants[pp] == creator)
        {
            cout << pp + 1 << " . " << participants[pp]->getUsername() << " (creator) " << endl;
        }
        else
        {
            //    / cout << (u->getUsername()).length() << endl;
            //  cout << u->getUsername() << endl;
            cout << pp + 1 << " . " << participants[pp]->getUsername() << endl;
        }
    }
    cout << "========================================================" << endl;
}

char GroupConversation::getType()
{
    return GROUP_CONV;
}
#endif
