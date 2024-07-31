#include "headers.hpp"

using namespace std;

int main()
{
    // Creating Users
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan3@gmail.com");
    User *u4 = new User("nar1", "nar1password", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2password", "nar2@gmail.com");
    User *u6 = new User("nar3", "nar3password", "nar3@gmail.com");
    User *u7 = new User("nar4", "nar4password", "nar4@gmail.com");
    User *u8 = new User("alex", "alexpass", "alex@gmail.com");
    User *u9 = new User("chris", "chrispass", "chris@gmail.com");
    User *u10 = new User("sam", "sampass", "sam@gmail.com");

    Post *p1 = new Post("Example post 1 from " + u2->getUsername(), u2, 0, 0);
    Post *p2 = new Post("Example post 2 from " + u3->getUsername(), u3, 0, 0);
    Post *p3 = new Post("Example post 3 from " + u5->getUsername(), u5, 0, 0);
    Post *p4 = new Post("Example post 4 from " + u1->getUsername(), u1, 0, 0);
    Post *p5 = new Post("Example post 5 from " + u6->getUsername(), u6, 0, 0);
    Post *p6 = new Post("Example post 6 from " + u6->getUsername(), u6, 0, 0);
    Post *p7 = new Post("Example post 7 from " + u3->getUsername(), u3, 0, 0);
    Post *p8 = new Post("Example post 8 from " + u1->getUsername(), u1, 0, 0);
    Post *p9 = new Post("Example post 9 from " + u7->getUsername(), u7, 0, 0);
    Post *p10 = new Post("Example post 10 from " + u5->getUsername(), u5, 0, 0);
    Post *p11 = new Post("Example post 11 from " + u5->getUsername(), u5, 0, 0);

    vector<User *> us = {u1, u2, u3, u4, u5, u6, u7, u8, u9, u10};
    vector<Post *> ps = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11};

    for (auto p : ps)
    {
        allPosts.push_back(p);
    }

    // Storing Users
    for (int i = 0; i < us.size(); i++)
    {
        store_user(us[i]);
    }

    // Creating Conversations
    CommunityConversation *conv1 = new FreeJoinCommunity(u5);
    CommunityConversation *conv2 = new FreeJoinCommunity(u2);
    CommunityConversation *conv3 = new FreeJoinCommunity(u3);
    CommunityConversation *conv4 = new FreeJoinCommunity(u4);
    CommunityConversation *conv5 = new FreeJoinCommunity(u1);
    CommunityConversation *conv7 = new RequestBasedCommunity(u1);
    conv7->issueRequest(u5);
    Conversation *conv6 = new DMConversation(u5, u6);
    Conversation *dm1 = new DMConversation(u1, u2);

    conv1->setCommunityName(u5->getUsername(), "Birds");
    conv2->setCommunityName(u2->getUsername(), "Animals");
    conv3->setCommunityName(u3->getUsername(), "New York");
    conv4->setCommunityName(u4->getUsername(), "London");
    conv5->setCommunityName(u1->getUsername(), "Berlin");
    conv7->setCommunityName(u1->getUsername(), "CSK");

    conv1->setCommunityDescription(u5->getUsername(), "This is about the beautiful avain species.. birds .");
    conv2->setCommunityDescription(u2->getUsername(), "This is about those that roam in the wild .. beautiful species and creations .. ");
    conv4->setCommunityDescription(u4->getUsername(), "This is about the beautiful capital city , London in the united kingdom of europe ");
    conv5->setCommunityDescription(u1->getUsername(), "This is about the magnificent capital city of germany , berlin. ");
    conv3->setCommunityDescription(u3->getUsername(), "This is about the capital city of United states of america . The technical marvel ");
     conv7->setCommunityDescription(u1->getUsername(), "CSK - chennai's cricket team . ");
    
    Conversation *convs[] = {conv1, conv2, conv3, conv4, conv5, conv6, conv7};
    for (Conversation *c : convs)
    {
        store_conv(c);
        //  Community_Graph.addVertex(c);
    }

    store_conv(dm1);

    Community_Graph.convWeights();

    u1->addFriend(u2);
    u1->addFriend(u3);
    u2->addFriend(u3);
    u2->addFriend(u4);
    u3->addFriend(u4);
    u3->addFriend(u5);
    u4->addFriend(u5);
    u4->addFriend(u6);
    u5->addFriend(u6);
    u5->addFriend(u7);
    u6->addFriend(u7);
    u6->addFriend(u8);
    u7->addFriend(u8);
    u7->addFriend(u9);
    u8->addFriend(u9);
    u8->addFriend(u10);
    u9->addFriend(u10);
    u9->addFriend(u1);
    u10->addFriend(u1);
    u10->addFriend(u2);

    int mainChoice, loginChoice, creationChoice, recommendationsChoice, messageChoice;
    Story *st;
    banner_display();

    do
    {
        vector<Conversation *> myconvs;
        vector<Conversation *> RecommendedConvs;
        vector<Conversation *> available_conversations;
        vector<Conversation *> rbcomms;
        string commtype;
        int rbchoice;
        CommunityConversation *tempconv = nullptr;
        // Conversation *gc;
        Notification n;
        Conversation *conv_of_interest;
        int notificationselection;
        int convidx;
        int choiceforconvdisplay;
        string description;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice)
        {
        case 1:
        {
            // Login
            pair<bool, string> user_details = User::login();
            bool status = user_details.first;
            string uname = user_details.second;
            User *loginuser = nullptr;
            for (int i = 0; i < us.size(); i++)
            {
                if (us[i]->getUsername() == uname)
                {
                    loginuser = us[i];
                    break;
                }
            }

            if (!status)
            {
                cout << "Invalid Login Credentials. Try Again." << endl;
                break;
            }

            do
            {
                cout << endl;
                cout << "1. Creation tasks" << endl;
                cout << "2. View your recommended feed" << endl;
                cout << "3. View your profile" << endl;
                cout << "4. View your friends" << endl;
                cout << "5. View your DMs, Groups, Communities" << endl;
                cout << "6. Do admin work on your communties" << endl;
                cout << "7. View your notifications" << endl;
                cout << "8. View your stories" << endl;
                cout << "9. View your recommendations" << endl;
                cout << "10. Search activities" << endl;
                cout << "11. Go Back" << endl;
                cout << "12. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> loginChoice;

                switch (loginChoice)
                {
                case 1:
                    // Creation tasks submenu
                    do
                    {
                        cout << "\nCreation Tasks Menu:" << endl;
                        cout << "1. Create post" << endl;
                        cout << "2. Create a Direct messaging conversation" << endl;
                        cout << "3. Create a community" << endl;
                        cout << "4. Create a group with your friends" << endl;
                        cout << "5. Create a story" << endl;
                        cout << "6. Create polls" << endl;
                        cout << "7. Go back" << endl;
                        cout << "8. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> creationChoice;

                        switch (creationChoice)
                        {
                        case 1:
                            cout << "Create a Post" << endl;
                            // Add code to create a post
                            loginuser->create_post();
                            break;
                        case 2:
                        {
                            //  cout << "Create a Direct Messaging conversation" << endl;
                            Conversation *c = loginuser->createDMConversation();
                            if (c != nullptr)
                            {
                                c->create_interface();
                                do
                                {
                                    cout << "1. Send a Message" << endl;
                                    cout << "2. Back" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> messageChoice;
                                    Message *m1;
                                    switch (messageChoice)
                                    {
                                    case 1:
                                        m1 = prepare_message(loginuser);
                                        c->sendMessage(m1);
                                        c->create_interface();
                                        break;
                                    case 2:
                                        break;
                                    default:
                                        cout << "Invalid option!" << endl;
                                        break;
                                    }
                                } while (messageChoice != 2);
                            }
                            break;
                        }
                        case 3:
                        {
                            /// cout << "Community creation interface" << endl;
                            Conversation *c = loginuser->createCommunityConversation();
                            c->create_interface();
                            if (c != nullptr)
                            {
                                do
                                {
                                    cout << "1. Send a Message" << endl;
                                    cout << "2. Back" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> messageChoice;
                                    Message *m1;
                                    switch (messageChoice)
                                    {
                                    case 1:
                                        m1 = prepare_message(loginuser);
                                        c->sendMessage(m1);
                                        c->create_interface();
                                        break;
                                    case 2:
                                        break;
                                    default:
                                        cout << "Invalid option!" << endl;
                                        break;
                                    }
                                } while (messageChoice != 2);
                            }
                            break;
                        }
                        case 4:
                        {
                            // create group
                            Conversation *gc = loginuser->createGroup();
                            if (gc != nullptr)
                            {
                                gc->create_interface();
                                do
                                {
                                    cout << endl;
                                    cout << "1. Send a Message" << endl;
                                    cout << "2. Back" << endl;
                                    cout << "Enter your choice: ";
                                    cin >> messageChoice;
                                    Message *m1;
                                    switch (messageChoice)
                                    {
                                    case 1:
                                        m1 = prepare_message(loginuser);
                                        gc->sendMessage(m1);
                                        gc->create_interface();
                                        break;
                                    case 2:
                                        break;
                                    default:
                                        cout << "Invalid option!" << endl;
                                        break;
                                    }
                                } while (messageChoice != 2);
                            }
                        }
                        break;

                        case 5:
                            cout << endl
                                 << "Story creation interface" << endl;
                            st = new Story(loginuser);
                            st->create_story();
                            break;
                        case 6:
                        {
                            vector<Conversation*> allconvey = getallcomms();
                            vector<Conversation*> selected;
                            for(auto &c : allconvey){
                                if(c->getCreator()->getUsername() == loginuser->getUsername()){
                                    selected.push_back(c);
                                }
                            }
                            int i = 0;
                            cout << "Here are the communities that your'e an admin of " <<endl;
                            for(auto &c : selected){
                                cout << ++i << " . " << c->getCommunityName() << endl;
                            }
                            int choice2;
                            cout << "Select a community (0 to exit): ";
                            cin >> choice2;
                            if(choice2 == 0){
                                break;
                            }
                            else{
                                selected[choice2-1]->createPoll();
                            }

                        }
                        break;
                        case 7:
                            cout << "Going back.." << endl;
                            break;
                        case 8:
                            cout << "Exiting program. Goodbye!" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice! Please enter a number between 1 and 8." << endl;
                        }
                    } while (creationChoice != 7);
                    break;
                case 2:
                    // recommendation feed
                    loginuser->feed_recommendation();
                    break;
                case 3:
                    // my profile
                    loginuser->display_profile();
                    break;
                case 4:
                    // friends display
                    loginuser->display_friends();
                    break;
                case 5:
                    // view my dms and enter into it
                    available_conversations = display_available_convs(loginuser->getUsername());

                    do
                    {
                        cout << "Enter your choice (0 to exit): " << endl;
                        cin >> choiceforconvdisplay;
                        if (choiceforconvdisplay > available_conversations.size())
                        {
                            cout << "Invalid option" << endl;
                        }
                        else if (choiceforconvdisplay == 0)
                        {
                            break;
                        }
                        else
                        {
                            available_conversations[choiceforconvdisplay - 1]->create_interface();
                            do
                            {
                                cout << "1. Send a Message" << endl;
                                cout << "2. Back" << endl;
                                cout << "Enter your choice: ";
                                cin >> messageChoice;
                                Message *m1;
                                switch (messageChoice)
                                {
                                case 1:
                                    m1 = prepare_message(loginuser);
                                    available_conversations[choiceforconvdisplay - 1]->sendMessage(m1);
                                    available_conversations[choiceforconvdisplay - 1]->create_interface();
                                    break;
                                case 2:
                                    break;
                                default:
                                    cout << "Invalid option!" << endl;
                                    break;
                                }
                            } while (messageChoice != 2);
                        }
                    } while (choiceforconvdisplay > available_conversations.size() || choiceforconvdisplay == -1);
                    break;

                case 6:
                    // rb comms
                    rbcomms = displayRBCommunities(loginuser->getUsername());
                    if (rbcomms.size() == 0)
                    {
                        cout << "No admin work available" << endl;
                    }
                    else
                    {
                        cout << "Enter your choice (0 to exit) : ";
                        cin >> rbchoice;
                        if (rbchoice != 0)
                        {

                            do
                            {
                                if (rbchoice <= rbcomms.size())
                                {
                                    (rbcomms[rbchoice - 1])->acceptRequest(loginuser);
                                }
                                else
                                {
                                    cout << "Enter a valid option! " << endl;
                                }
                            } while (rbchoice > rbcomms.size());
                        }
                    }
                    break;
                case 7:
                    // notifications view
                    {
                        loginuser->displayNotifications();
                        cout << "Select a notification (0 to exit) ";

                        cin >> notificationselection;
                        if (notificationselection == 0)
                        {
                            break;
                        }

                        n = loginuser->notifications.search(notificationselection);
                        conv_of_interest = n.belongs_to;
                        conv_of_interest->create_interface();
                        do
                        {
                            cout << "1. Send a Message" << endl;
                            cout << "2. Back" << endl;
                            cout << "Enter your choice: ";
                            cin >> messageChoice;
                            Message *m1;
                            switch (messageChoice)
                            {
                            case 1:
                                m1 = prepare_message(loginuser);
                                conv_of_interest->sendMessage(m1);
                                conv_of_interest->create_interface();
                                break;
                            case 2:
                                break;
                            default:
                                cout << "Invalid option!" << endl;
                                break;
                            }
                        } while (messageChoice != 2);
                    }

                    break;
                case 8:
                    // view stories
                    {
                        for (Story *s : allstories)
                        {
                            if (s->author->getUsername() == loginuser->getUsername())
                            {
                                loginuser->my_stories.push_back(*s);
                            }
                        }
                        loginuser->displayStories();
                    }
                    break;
                case 9:
                    // View your recommendations submenu
                    do
                    {
                        cout << "1. View friend suggestions" << endl;
                        cout << "2. View your community recommendations" << endl;
                        cout << "3. Get tailor-made community suggestions based on your wish" << endl;
                        cout << "4. Go back" << endl;
                        cout << "5. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> recommendationsChoice;

                        switch (recommendationsChoice)
                        {
                        case 1:
                            cout << "Your friend suggestions" << endl;
                            loginuser->display_friend_suggestions();
                            break;
                        case 2:
                            cout << "Communities that we recommend" << endl;
                            myconvs = available_convs(user_details.second);
                            {
                                int ccc = 0;
                                for (int i = 0; i < myconvs.size(); i++)
                                {
                                    if (myconvs[i]->priority != 2)
                                    {
                                        cout << "Iteration: " << i << endl;
                                        Community_Graph.convWeights();
                                        list<int> nearest_comms = prims(Community_Graph, myconvs[i]);
                                        for (int j : nearest_comms)
                                        {
                                            Conversation *c = micUGComm[j];
                                            if (c->getCommunityName() != myconvs[i]->getCommunityName())
                                            {
                                                RecommendedConvs.push_back(c);
                                                if (c->priority == 1)
                                                {
                                                    cout << ++ccc << " . " << c->getCommunityName() << " (Free to Join) " << endl;
                                                }
                                                else
                                                {
                                                    cout << ++ccc << " . " << c->getCommunityName() << " (Admin approval required) " << endl;
                                                }
                                            }
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
                                Conversation *c = RecommendedConvs[convidx - 1];
                                if (c->priority == 1.5)
                                {
                                    cout << "Request has been sent to the admin!" << endl;
                                    c->issueRequest(loginuser);
                                }
                                else
                                {
                                    c->joinCommunity(loginuser);
                                }
                                // c->joinCommunity(loginuser);
                            }
                            break;
                        case 3:
                            cout << "Get tailor-made community suggestions" << endl;
                            Community_Graph.convWeights();
                            cout << "Describe what you expect (include keywords for better suggestions): " << endl;
                            // to clear the newline character left in the buffer
                            getline(cin >> ws, description);
                            tempconv = new FreeJoinCommunity(loginuser);
                            tempconv->setCommunityDescription(loginuser->getUsername(), description);
                            {
                                vector<Conversation *> suggestions = Community_Graph.suggestConvsFloyd(tempconv);
                                cout << "We suggest you to join the following communities" << endl;

                                for (int i = 0; i < suggestions.size(); i++)
                                {
                                    cout << i + 1 << " . " << suggestions[i]->getCommunityName() << endl;
                                }
                                cout << "Wish to join any of these Communities (-1 for no/ specify the number of community) : ";
                                cin >> convidx;
                                if (convidx == -1)
                                {
                                    break;
                                }
                                else
                                {
                                    Conversation *c = suggestions[convidx - 1];
                                    if (c->priority == 1.5)
                                    {
                                        cout << "Request has been sent to the admin!" << endl;
                                        c->issueRequest(loginuser);
                                    }
                                    else
                                    {
                                        c->joinCommunity(loginuser);
                                    }
                                }
                            }
                            break;
                        case 4:
                            cout << "Returning to Login Menu." << endl;
                            break;
                        case 5:
                            cout << "Exiting program. Goodbye!" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice! Please enter a number between 1 and 5." << endl;
                        }
                    } while (recommendationsChoice != 4);
                    break;
                case 10:
                    // search activity.
                    {
                        int schoice;
                        do
                        {
                            cout << "1.Search User\n2.Search Community\n3.Exit" << endl;
                            cout << "Enter your choice: ";
                            cin >> schoice;
                            switch (schoice)
                            {
                            case 1:
                            {
                                cout << "Search user: ";
                                string searchbar;
                                getline(cin >> ws, searchbar);
                                vector<User> allusers = allusersearch();
                                vector<int> lcslengths(allusers.size(), 0);
                                for (int i = 0; i < allusers.size(); i++)
                                {
                                    lcslengths[i] = lcsuser(allusers[i].getUsername(), searchbar);
                                }
                                list<pair<int, int>> forsorting;
                                for (int i = 0; i < lcslengths.size(); i++)
                                {

                                    if (allusers[i].getUsername() != loginuser->getUsername())
                                    {
                                        forsorting.push_back({i, lcslengths[i]});
                                    }
                                }
                                forsorting.sort(sortingfn);
                                int i = 0;
                                vector<pair<int, int>> sortvector;
                                for (auto &p : forsorting)
                                {
                                    sortvector.push_back(p);
                                }
                                for (auto &p : sortvector)
                                {
                                    if (i == 5)
                                    {
                                        break;
                                    }
                                    int idx = p.first;
                                    cout << i + 1 << " . " << allusers[idx].getUsername() << endl;
                                    i++;
                                }
                                int unum;
                                cout << "Enter user number: ";
                                cin >> unum;
                                int inchoice;

                                do
                                {
                                    cout << "1. Display Profile\n2. Add as Friend\n3.Exit" << endl;

                                    cout << "Enter your choice: ";
                                    cin >> inchoice;
                                    switch (inchoice)
                                    {
                                    case 1:
                                    {
                                        allusers[sortvector[unum - 1].first].display_profile(1);
                                    }
                                    break;
                                    case 2:
                                    {
                                        vector<User> friendsofmine = findfriends(loginuser);
                                        bool ok = true;
                                        for (User u : friendsofmine)
                                        {
                                            if (u.getUsername() == allusers[sortvector[unum - 1].first].getUsername())
                                            {
                                                cout << "Already friends!" << endl;
                                                ok = false;
                                                break;
                                            }
                                        }
                                        if (ok)
                                        {
                                            loginuser->addFriend(&allusers[sortvector[unum - 1].first]);
                                            cout << "Friend successfully added" << endl;
                                        }
                                    }
                                    break;
                                    case 3:
                                    {
                                        cout << "Going back" << endl;
                                    }
                                    break;
                                    default:
                                        cout << "Invalid option" << endl;
                                    }
                                } while (inchoice != 3);
                            }
                            break;
                            case 2:
                            {
                                // search communities;
                                vector<Conversation *> allcommssys = getallcomms();
                                vector<Conversation *> myconversations = available_convs(loginuser->getUsername());
                                vector<Conversation *> allcomms;
                                for (auto &c : allcommssys)
                                {
                                    bool f = true;
                                    for (auto &c1 : myconversations)
                                    {
                                        if (c1->getCommunityName() == c->getCommunityName())
                                        {
                                            f = false;
                                            break;
                                        }
                                    }
                                    if (f)
                                    {
                                        allcomms.push_back(c);
                                    }
                                }
                                int q = 0;
                                for (auto &c : allcomms)
                                {
                                    if (c->priority == 1)
                                    {
                                        cout << ++q << " " << c->getCommunityName() << " (Free to Join)" << endl;
                                    }
                                    else
                                    {
                                        cout << ++q << " " << c->getCommunityName() << " (Admin approval required)" << endl;
                                    }
                                }
                                int convcc;
                                cout << "Enter your choice: ";
                                cin >> convcc;
                                cout << "Joining the community..." << endl;
                                if (allcomms[convcc - 1]->priority != 1)
                                {
                                    allcomms[convcc - 1]->issueRequest(loginuser);
                                    cout << "Request sent" << endl;
                                }
                                else
                                {
                                    allcomms[convcc - 1]->joinCommunity(loginuser);
                                    cout << "Joined successfully" << endl;
                                }
                            }
                            break;
                            case 3:
                            {
                                cout << "Going back" << endl;
                            }
                            break;
                            default:
                                cout << "Invalid option" << endl;
                                break;
                            }
                        } while (schoice != 3);
                    }
                case 11:
                    cout << "Returning to Main Menu." << endl;
                    break;
                case 12:
                    cout << "Exiting program. Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 12." << endl;
                }
            } while (loginChoice != 11);
            break;
        }

        case 2:
            // Register option
            {
                User *new_user = User::register_user();
                us.push_back(new_user);
                break;
            }
        case 3:
            cout << "Exiting.." << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1, 2 and 3." << endl;
            break;
        }
    } while (mainChoice != 3);

    return 0;
}
