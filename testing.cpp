#include "headers.hpp"

int main()
{

    /*
        1. Display all the conversations that user is a part of.
        2. Enable them to select a conversation
        3. Create a conversation from that.
        4. Allow them to message in that conversation if they desire.
        5. Or they can go back one level up.
    */

   User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");


    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for (int i = 0; i < 6; i++)
    {
        store_user(us[i]);
    }

    u1->addFriend(u2);
    u2->addFriend(u3);
    u3->addFriend(u1);
    u4->addFriend(u5);
    u5->addFriend(u1);
    u4->addFriend(u1);

     CommunityConversation *conv1 = new FreeJoinCommunity(u1);
     conv1->setCommunityName(u1->getUsername(), "vadakkana");
    CommunityConversation *conv2 = new FreeJoinCommunity(u2);
    CommunityConversation *conv3 = new FreeJoinCommunity(u3);
    CommunityConversation *conv4 = new FreeJoinCommunity(u4);
    CommunityConversation *conv5 = new FreeJoinCommunity(u5);
    Conversation *conv6 = new DMConversation(u5, u6);

    store_conv(conv1);
    store_conv(conv2);
    store_conv(conv3);
    store_conv(conv4);
    store_conv(conv5);
    store_conv(conv6);

    Post *p1 = new Post("Example post 1 from " + u2->getUsername(), u2);
    Post *p2 = new Post("Example post 2 from " + u3->getUsername(), u3);
    Post *p3 = new Post("Example post 3 from " + u5->getUsername(), u5);
    Post *p4 = new Post("Example post 4 from " + u1->getUsername(), u1);
    Post *p5 = new Post("Example post 5 from " + u6->getUsername(), u6);
    Post *p6 = new Post("Example post 6 from " + u6->getUsername(), u6);
    Post *p7 = new Post("Example post 7 from " + u3->getUsername(), u3);
    Post *p8 = new Post("Example post 8 from " + u1->getUsername(), u1);
    Post *p9 = new Post("Example post 9 from " + u7->getUsername(), u7);
    Post *p10 = new Post("Example post 10 from " + u5->getUsername(), u5);
    Post *p11 = new Post("Example post 11 from " + u5->getUsername(), u5);

    Post *ps[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11};

    for(auto i : ps){
        AllPosts.push_back(i);
    }

    pair<bool, string> p = User::login();

    User *login_user;

    for(User *u : us){
        if(p.second == u->getUsername()){
            login_user = u;
            break;
        }
    }

    if (p.first)
    {
        //Conversation* created_dm = login_user->createDMConversation();
        login_user->display_friend_suggestions();
        // for(User *u : created_dm->participants){
        //     cout << u->getUsername() <<endl;
        // }
    }
    
//    Conversation *c = search_node(u1->getUsername(), u2->getUsername());

}
