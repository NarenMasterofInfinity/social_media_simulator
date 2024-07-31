#include "headers.hpp"

int main()
{
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

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

    list<Edge> T;
    map<int, list<int>> m;
    pair<list<Edge>, map<int, list<int>>> Clusters = kruskal(Similarity_Graph);

    T = Clusters.first;
    m = Clusters.second;

    cout << k << " predoaminant communities of people are: " << endl;
    int i = 0;
    for (map<int, list<int>>::iterator mi = m.begin(); mi != m.end(); mi++)
    {
        int key = mi->first;
        list<int> val = mi->second;

        ++i;
        cout << "These belong in cluster " << i << endl;
        int j = 0;
        for (int v : val)
        {
            if (v == 0)
            {
                v = Similarity_Graph.nv;
            }
            cout << ++j << " . " << miuUG[v] << endl;
        }
    }
    return 0;
}
