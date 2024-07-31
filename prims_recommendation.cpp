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

    for (int i = 0; i < 6; i++)
    {
        store_user(us[i]);
        Similarity_Graph.addVertex(us[i]);
    }

    CommunityConversation *conv1 = new FreeJoinCommunity(u5);
    CommunityConversation *conv2 = new FreeJoinCommunity(u2);
    CommunityConversation *conv3 = new FreeJoinCommunity(u3);
    CommunityConversation *conv4 = new FreeJoinCommunity(u4);
    CommunityConversation *conv5 = new FreeJoinCommunity(u1);
    Conversation *conv6 = new DMConversation(u5, u6);

    conv1->setCommunityName(u5->getUsername(), "Birds");
    conv2->setCommunityName(u2->getUsername(), "Animals");
    conv3->setCommunityName(u3->getUsername(), "New York");
    conv4->setCommunityName(u4->getUsername(), "London");
    conv5->setCommunityName(u1->getUsername(), "Berlin");

    conv1->setCommunityDescription(u5->getUsername(), "Welcome to our vibrant bird community, where diversity thrives amidst lush foliage. From majestic eagles to petite hummingbirds, each bird contributes to our tapestry of camaraderie and cooperation. Explore boundless skies, share stories, and find sanctuary among friends. Together, we soar to new heights, embracing the beauty of nature. Welcome home.");
    conv2->setCommunityDescription(u2->getUsername(), "Welcome to our bustling animal community, where diversity thrives in every paw print and hoof beat. From the regal lions to the playful otters, each creature adds its unique charm to our tapestry of camaraderie. Explore the wild wonders, share tales, and find kinship amidst nature's embrace. Welcome to the pack.");
    conv3->setCommunityDescription(u3->getUsername(), "Welcome to the bustling metropolis of New York City, where skyscrapers reach for the heavens and the heartbeat of the city never sleeps. Amidst the hustle and bustle, diversity flourishes in every corner, from the neon-lit streets of Times Square to the serene oasis of Central Park. Explore iconic landmarks, savor culinary delights, and embrace the vibrant energy of the city that never ceases to inspire. Welcome to the concrete jungle where dreams are made and stories unfold at every turn.");
    conv4->setCommunityDescription(u4->getUsername(), "Welcome to the historic metropolis of London, where ancient architecture meets modern innovation, and the River Thames weaves through centuries of storied tales. Amidst the iconic landmarks like Big Ben and the Tower Bridge, diversity thrives in the bustling streets of Soho and the serene parks of Hyde Park. Explore cultural riches, indulge in culinary delights, and immerse yourself in the timeless charm of a city where tradition and modernity intertwine. Welcome to London, where every cobblestone holds a piece of history and every corner beckons with possibility.");
    conv5->setCommunityDescription(u1->getUsername(), "Welcome to the vibrant city of Berlin, where history and innovation converge amidst a backdrop of cultural richness. From the remnants of the Berlin Wall to the contemporary art scene of Kreuzberg, diversity flourishes in every neighborhood. Explore iconic landmarks, savor culinary delights from around the globe, and embrace the creative energy that pulses through the city streets. Welcome to Berlin, where the past meets the present, and every corner offers a new adventure waiting to unfold.");

    conv2->joinCommunity(us[6]);

    Conversation *convs[] = {conv1, conv2, conv3, conv4, conv5, conv6};
    for (Conversation *c : convs)
    {
        store_conv(c);
       // Community_Graph.addVertex(c);
    }

    Community_Graph.convWeights();
    
   
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

    if (status)
    {
        int choice = 20;
        vector<Conversation *> myconvs;
        do
        {
            int convchoice;
            int convidx;
            list<int> nearest_comms;
            map<int, int> DMBypass;
            int ccc = 0;
            Conversation *c;
            vector<Conversation*> RecommendedConvs;
            cout << "1. Display my Conversations" << endl;
            cout << "2. View my Community Recommendations" << endl;
            cout << "3. Exit" << endl;
            cout << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            case 1:
                cout << "Conversations your'e a part of : "<<endl;
                myconvs = display_available_convs(login_details.second);
                cout << endl;
                break;
            case 2:
                cout << "Communities that we recommend: "<<endl;
                myconvs = available_convs(login_details.second);
                for (int i = 0; i < myconvs.size(); i++)
                {
                    if (myconvs[i]->priority != 2)
                    {
                        nearest_comms = prims(Community_Graph, myconvs[i]);
                        for (int j : nearest_comms)
                        {
                            c = micUGComm[j];
                            if (c->getCommunityName() != myconvs[i]->getCommunityName())
                            {
                                RecommendedConvs.push_back(c);
                                cout << ++ccc << " . " << c->getCommunityName() << endl;
                            }
                        }
                    }
                }
                cout << endl;
                cout << "Wish to join a Conversation (-1 for no/ specify the number of community) : ";
                cin >> convidx;
                if (convidx == -1)
                {
                    break;
                }
                else
                {
                    c = RecommendedConvs[convidx-1];
                    c->joinCommunity(loginuser);
                }
                break;
            case 3:
            default:
                break;
            }

        } while (choice < 3);
    }
}
