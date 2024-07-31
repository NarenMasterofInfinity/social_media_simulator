
#include "conv_methods.h"
#include "user_db.h"
#include "group_methods.h"

int main()
{
    int session = 0;

    User *user1 = new User("user1", "pass", "user1@gmail.com");
    User *user2 = new User("user2", "pass", "user@gmail.com");
    User *user3 = new User("user3", "pass", "user3@gmail.com");

    store_user(user1);
    store_user(user2);
    store_user(user3);

    setSession(&session);

    if (session)
    {

        char group_or_normal;
        bool g;
        int count;

        while (true)
        {
            cout << "Do you wish to start a duo or group chat?(g for group /d for duo) ";
            cin >> group_or_normal;
            if (group_or_normal == 'g')
            {
                g = true;

                cout << "The number of group members: ";
                cin >> count;
                string group_name;

                Conversation *conv1 = new Conversation(g, count, user1);

                cout << "Enter group name: ";
                cin >> group_name;

                Group *g1 = new Group(user1, group_name);

                g1->add_members(count);
                conv1->add_participants(g1);
                conv1->display_participants();

                delete g1;
                delete conv1;

                break;
            }
            else if (group_or_normal == 'd')
            {
                g = false;
                count = 2;

                Conversation *conv1 = new Conversation(g, count, user1);
                conv1->add_participants(user1, user2);
                conv1->display_participants();

                delete conv1;

                break;
            }
            else
            {
                cout << "Invalid option" << endl;
            }
        }
    }
    else
    {
        cout << "Session not started!";
    }

    User **users;

    int i = 0;
    users = (User **)malloc(sizeof(User *) * USER_MAX);

    users[i++] = user1;
    users[i++] = user2;
    users[i++] = user3;

    cout << "Creating a group by passing users directly" << endl;
    Group *g2 = new Group(user1, users, "group_abc");

    cout << "Using copy constructor" << endl;
    Group *g3 = new Group(*g2);

    delete g3;

    delete users;
}
