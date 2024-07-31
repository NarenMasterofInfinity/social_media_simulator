#include "headers.hpp"

int main()
{
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    Post *p1 = new Post("Example post 1 from "+u2->getUsername(), u2);
    Post *p2 = new Post("Example post 2 from "+u3->getUsername(), u3);
    Post *p3 = new Post("Example post 3 from "+u5->getUsername(), u5);
    Post *p4 = new Post("Example post 4 from "+u1->getUsername(), u1);
    Post *p5 = new Post("Example post 5 from "+u6->getUsername(), u6);
    Post *p6 = new Post("Example post 6 from "+u6->getUsername(), u6);
    Post *p7 = new Post("Example post 7 from "+u3->getUsername(), u3);
    Post *p8 = new Post("Example post 8 from "+u1->getUsername(), u1);
    Post *p9 = new Post("Example post 9 from "+u7->getUsername(), u7);
    Post *p10 = new Post("Example post 10 from "+u5->getUsername(), u5);
    Post *p11 = new Post("Example post 11 from "+u5->getUsername(), u5);

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};
    Post *ps[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11};

    for (User *&u : us)
    {
        store_user(u);
        Similarity_Graph.addVertex(u);
    }

    CommunityConversation *conv1 = new FreeJoinCommunity(u1);
    CommunityConversation *conv2 = new FreeJoinCommunity(u2);
    CommunityConversation *conv3 = new FreeJoinCommunity(u3);
    CommunityConversation *conv4 = new FreeJoinCommunity(u4);
    CommunityConversation *conv5 = new FreeJoinCommunity(u5);
    Conversation *conv6 = new DMConversation(u5, u6);

    // for (int i = 0; i < 20; i++)
    // {
    //     conv1->joinCommunity(us[rand() % 7]);
    //     conv2->joinCommunity(us[rand() % 7]);
    //     conv3->joinCommunity(us[rand() % 7]);
    //     conv4->joinCommunity(us[rand() % 7]);
    //     conv5->joinCommunity(us[rand() % 7]);
    // }

    conv2->joinCommunity(us[6]);

    Conversation *convs[] = {conv1, conv2, conv3, conv4, conv5};

    for (Conversation *c : convs)
    {
        store_conv(c);
    }

    store_conv(conv6);

    Similarity_Graph.addEdges();

    // for ( Edge e : Similarity_Graph.E){
    //     cout << e.u << " " <<e.v << " "<<e.weight<<endl;
    // }

    pair<bool, string> login_details = User::login();
    string username = login_details.second;
    bool status = login_details.first;
    User *loginuser;
    for (int i = 0; i < 6; i++)
    {
        if (us[i]->getUsername() == username)
        {
            loginuser = us[i];
            break;
        }
    }

    list<Edge> T;
    map<int, list<int>> m;
    pair<list<Edge>, map<int, list<int>>> Clusters = kruskal(Similarity_Graph);

    list<int> desired_users;

    T = Clusters.first;
    m = Clusters.second;

    cout << "Analysing from the clusters created by the kruskal algorithm " << endl;
    int i = 0;
    for (map<int, list<int>>::iterator mi = m.begin(); mi != m.end(); mi++)
    {
        int key = mi->first;
        list<int> val = mi->second;

        ++i;

        int j = 0;
        for (int v : val)
        {
            if (v == 0)
            {
                v = Similarity_Graph.nv;
            }
            string un = miuUG[v];
            if (un == username)
            {
                desired_users = val;
                break;
            }
        }
    }

    cout << "Your recommended posts"<<endl;

    for(int i = 0; i < 10; i++){
        for(int v : desired_users){
            if (v == 0)
            {
                v = Similarity_Graph.nv;
            }
            if(ps[i]->getAuthor()->getUsername() == miuUG[v] && miuUG[v] != username){
                cout << "======================================="<<endl;
                cout << "               Post" <<endl;
                cout << "======================================="<<endl;

                cout << ps[i]->getContent() << endl;

                cout << "=======================================" <<endl;
            }
        }
    }
    return 0;
}
