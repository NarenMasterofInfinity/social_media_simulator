#include "headers.hpp"

using namespace std;

int main()
{

    User *u1 = new User("user1", "naren3", "naren@gmail.com");
    User *u2 = new User("user2", "jan3", "jan@gmail.com");
    User *u3 = new User("user3", "jan3", "jan@gmail.com");
    User *u4 = new User("user4", "naren3", "nar1@gmail.com");
    User *u5 = new User("user5", "naren3", "nar1@gmail.com");
    User *u6 = new User("user6", "naren3", "nar1@gmail.com");
    User *u7 = new User("user7", "naren3", "nar1@gmail.com");
    User *u8 = new User("user8", "naren3", "nar1@gmail.com");
    User *u9 = new User("user9", "naren3", "nar1@gmail.com");
    User *u10 = new User("user10", "naren3", "nar1@gmail.com");
    User *u11 = new User("user11", "naren3", "nar1@gmail.com");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11};

    for (User *u : us)
    {
        store_user(u);
        // this adds the user to the AVLTree and the graph..
    }
    u1->addFriend(u2);
    u2->addFriend(u3);
    u3->addFriend(u1);
    u4->addFriend(u5);
    u5->addFriend(u1);
    u11->addFriend(u8);
    u7->addFriend(u10);
    u9->addFriend(u10);
    u11->addFriend(u10);
    u8->addFriend(u11);
    u10->addFriend(u7);
    u9->addFriend(u8);
    u4->addFriend(u1);

    vector<User> friends = findfriends(u11);

    for(auto i : friends){
        cout << i.getUsername();
    }
    return 0;
}