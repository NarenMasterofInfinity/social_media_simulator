#include "classes.h"
#include "user_db.h"

#ifndef GROUP_METHODS_H
#define GROUP_METHODS_H
void Group::add_members(int count)
{
    cout << "|=====================================================|" << endl;
    cout << "|                   Add participants                  |" << endl;
    cout << "|=====================================================|" << endl;
    string usernames[count];
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
            this->users[i] = User::search_user(usernames[i]);
        }
    }
}
#endif
