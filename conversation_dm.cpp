#include "classes.h"
#include "conv_methods.h"
#include "user_methods.h"
#include "conv_db.h"

int main()
{
    int session = 0;

    User *user1 = new User("hans", "pass", "user1@gmail.com");
    User *user2 = new User("zimmer", "pass2", "zimmer@gmail.com");
    User *user3 = new User("user3", "pass", "user3@gmail.com");

    store_user(user1);
    store_user(user2);
    store_user(user3);

    setSession(&session);

    if (session)
    {
        bool g = false, status;
        int count = 2;

        Conversation *conv1 = new Conversation(g, count, user1);

        conv1->add_participants(user1, user2);

        store_conv(conv1);


        User u = *user1, v = *user2;
        status = u > v; // u sends message to v
        status = status ? v > u : false;
        status = status ? u > v : false;

        if (status)
            conv1->create_interface_dm();
    }
}