#include "classes.hpp"
#include "user_db.hpp"
#include "conv_db.hpp"
#include "kruskal.hpp"

#ifndef USER_METHODS_H
#define USER_METHODS_H

#define DISPLAY_THRESHOLD 10

void User::setUsername(string username)
{
    this->username = username;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPassword(string password)
{
    this->password = password;
}

string User::getEmail()
{
    return email;
}

string User::getPassword()
{
    return password;
}

string User::getUsername()
{
    return username;
}

User *User::search_user(string username)
{

    User *us = new User(username);
    Node<User> *u = available_users.search(available_users.root, *us);
    if (u)
    {
        User ussr = u->val;
        User *user_to_return;
        user_to_return = &ussr;
        return user_to_return;
    }
    return nullptr;
}

User User::search_user_no_pointer(string username)
{

    User *us = new User(username);
    Node<User> *u = available_users.search(available_users.root, *us);
    if (u)
    {

        return u->val;
    }
    User fl;
    return fl;
}

// bool operator>(User user1, User user2)
// {
//     Conversation *c = search_node(user1.getUsername(), user2.getUsername());
//     if (true)
//     {
//         User *u = &user1;
//         c->sendText(u);
//         return true;
//     }
//     return false;
// }
pair<bool, string> User::login()
{

    string uname, passw;
    cout << "====================Login======================" << endl;
    cout << "Enter username : ";
    cin >> uname;
    cout << "Enter password : ";
    cin >> passw;
    User *u = User::search_user(uname);
    if (!u)
    {
        cout << "Such a user doesn't exist!" << endl;
        cout << "===============================================" << endl;
        return {false, uname};
    }
    if (passw != u->getPassword())
    {
        cout << "Wrong password" << endl;
        cout << "===============================================" << endl;
        return {false, uname};
    }
    cout << "===============================================" << endl;
    cout << "Successfully logged in! " << endl;
    return {true, uname};
}

User *User::register_user()
{
    cout << "=======================Register=====================" << endl;
    int okay = 1;
    string uname, umail, upass;
    User *u;
    do
    {
        cout << "Enter your username: ";
        getline(cin >> ws, uname);
        User *ptr = User::search_user(uname);
        if (nullptr == ptr)
        {
            u = new User(uname);
            cout << "Enter your email id: " << endl;
            cin >> umail;
            cout << "Enter your password: " << endl;
            cin >> upass;
            u->setEmail(umail);
            u->setPassword(upass);
            cout << "you have succesfully registered." << endl;
            store_user(u);
            return u;
        }
        else
        {
            okay = 0;
            cout << "Such a user already exists!. Please try again with a different name. " << endl;
            cout << "Do you wish to exit? (1 for no/ -1 for exit): ";
            int choice;
            cin >> choice;
            if (choice == -1)
            {
                okay = -1;
            }
        }
    } while (okay != 1 && okay != -1);
    return nullptr;
}
vector<User> findfriends(User *u, int level = 1)
{
    vector<User> users;
    global_users->bfslevelutil(mui[u->getUsername()], users, 1);
    return users;
}

Conversation *User::createGroup()
{
    cout << endl
         << "Welcome to Group creation interface!" << endl;
    Conversation *c = new GroupConversation(this);
    string gname;
    cout << "Enter the Group name (-1 to exit): ";
    getline(cin >> ws, gname);
    if (gname == "-1")
    {
        return nullptr;
    }
    c->setGroupName(gname);
    c->addMembers(this);
    store_conv(c);
    cout << "Group successfully created" << endl;
    return c;
}

void User::addFriend(User *u)
{

    global_users->addEdge(this, u);
}

void User::displayNotifications()
{
    notifications.sorted_display();
}

void User::display_friends()
{
    vector<User> friends = findfriends(this);
    int i = 0;
    for (auto ufriend : friends)
    {
        cout << ++i << ". " << ufriend.getUsername() << endl;
    }
    /*
        menu : 1. exit, 2. display profile, then view posts
    */
    string uname;
    cout << "Enter the friend name: (-1 to exit):  ";
    cin >> uname;
    if (uname == "-1")
    {
        return;
    }

    int ch;
    do
    {
        cout << "1. Display profile" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        if (ch == 1)
        {
            int idx = 0;
            for (User u : friends)
            {
                if (u.getUsername() == uname)
                {
                    break;
                }
                idx++;
            }

            friends[idx].display_profile(1);
            ch = 2;
        }

    } while (ch != 2);
}

bool User::operator<=(User u)
{
    return this->getUsername() <= u.getUsername();
}
bool User::operator<(User u)
{
    return this->getUsername() < u.getUsername();
}
bool User::operator>(User u)
{
    // return false;

    return this->getUsername() > u.getUsername();
}
bool User::operator>=(User u)
{
    return this->getUsername() >= u.getUsername();
}

bool User::operator==(User u)
{
    // return false;
    return this->getUsername() == u.getUsername();
}

bool User::operator!=(User u)
{
    return this->getUsername() != u.getUsername();
}

void User::display_profile(int lnt = 0)
{
    cout << "=======================Profile========================" << endl;
    if (nullptr != profile_picture)
    {
        profile_picture->display();
    }
    else
    {
        if (lnt == 0)
        {
            cout << "You have not added profile picture" << endl;
        }
        else
        {
            cout << username << " has no profile picture" << endl;
        }
    }
    cout << "@" << username << endl;
    cout << "Email: " << email << endl;
    if (bio.length() != 0)
    {
        cout << "Bio: " << bio << endl;
    }
    else
    {
        cout << "No bio available " << endl;
    }
    cout << "=======================================================" << endl;

    int choice = 0;
    if (lnt == 0)
    {
        do
        {
            cout << "1. Display my posts." << endl;
            cout << "2. Display saved posts." << endl;
            cout << "3. Add a Profile picture. " << endl;
            cout << "4. Add a bio. " << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            string path;
            switch (choice)
            {
            case 1:
                if (my_posts.size() == 0)
                {
                    cout << "You have not posted anything." << endl;
                }
                else
                {
                    for (auto post : my_posts)
                    {
                        post->display();
                    }
                }
                break;
            case 2:
                if (saved_posts.size() == 0)
                {
                    cout << "You have no saved posts!." << endl;
                }
                else
                {
                    for (auto post : saved_posts)
                    {
                        post->display();
                    }
                }
                break;
            case 3:
                cout << "Enter the image path: ";
                getline(cin >> ws, path);
                profile_picture = new Image(path);

                if (nullptr == profile_picture)
                {
                    cout << "Profile picture added!" << endl;
                }
                else
                {
                    cout << "Profile picture changed!" << endl;
                }
                //   display_profile();
                break;
            case 4:
                cout << "Enter your bio: ";
                getline(cin >> ws, bio);
                cout << "Bio updated successfully." << endl;
                // display_profile();
                break;
            case 5:

                break;
            default:
                choice = 5;
                cout << "Exiting.." << endl;

                break;
            }
        } while (choice != 5 && choice != 0);
    }
    else
    {
        do
        {
            cout << "1. Display their posts" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1)
            {
                for (auto post : allPosts)
                {
                    if(post->getAuthor()->getUsername() == username){
                           post->display();
                    }
                }
            }
            else if (choice == 2)
            {
                return;
            }
            else if (choice != 2)
            {
                cout << "Invalid option" << endl;
            }
        } while (choice == 1);
    }
}
void Graph::bfslevelutil(int ui, vector<User> &users, int levelat)
{
    queue<int> q;
    queue<int> level;
    q.push(ui);
    vector<bool> visited(nv, false);
    visited[ui] = true;
    level.push(0);
    while (!q.empty())
    {
        int user = q.front();
        q.pop();
        int l = level.front();
        level.pop();

        if (l == levelat)
        {
            User u = User::search_user_no_pointer(miu[user]);
            users.push_back(u);
        }
        if (l > levelat)
        {
            break;
        }
        for (int i = 0; i < nv; i++)
        {
            if (adj[user][i] == 1 && !visited[i])
            {
                q.push(i);
                level.push(l + 1);
                visited[i] = true;
            }
        }
    }
}

bool comparatorfn(Post *p1, Post *p2)
{
    int w1 = p1->no_of_likes + p1->no_of_shares;
    int w2 = p1->no_of_likes + p1->no_of_shares;

    return w1 < w2;
}
void User::feed_recommendation()
{
    Similarity_Graph.addEdges();
    list<Edge> T;
    map<int, list<int>> m;
    pair<list<Edge>, map<int, list<int>>> Clusters = kruskal(Similarity_Graph);

    list<int> desired_users;
    vector<Post *> desired_posts;

    T = Clusters.first;
    m = Clusters.second;

    for (auto mi = m.begin(); mi != m.end(); ++mi)
    {
        auto val = mi->second;

        for (int &v : val)
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

    bool f = true;
    for (auto i : allPosts)
    {
        for (int v : desired_users)
        {
            if (v == 0)
            {
                v = Similarity_Graph.nv;
            }
            if (i->getAuthor()->getUsername() == miuUG[v] && miuUG[v] != username)
            {
                f = false;
                desired_posts.push_back(i);
            }
        }
    }

    bool f1 = true;
    if (f)
    {
        cout << "You have no recommended posts. Here are the trending posts!" << endl;
        list<Post *> temp_posts;
        for (auto p : allPosts)
        {
            temp_posts.push_back(p);
        }
        temp_posts.sort(comparatorfn);
        int counterpost = 0;
        for (auto p : temp_posts)
        {
            allPosts[counterpost++] = p;
        }
        vector<Post *> needed_posts;

        for (auto p : allPosts)
        {
            int w = p->no_of_shares + p->no_of_likes;
            if (w >= DISPLAY_THRESHOLD)
            {
                needed_posts.push_back(p);
                f1 = false;
            }
        }

        for (auto pointer = needed_posts.begin(); pointer != needed_posts.end();)
        {
            int ch1;
            (*pointer)->display_post_details();
            cout << "1. Next" << endl;
            cout << "2. Prev" << endl;
            cout << "3. Interact" << endl;
            cout << "4. Display Comments" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice : ";
            cin >> ch1;
            switch (ch1)
            {
            case 1:
                if (pointer + 1 != needed_posts.end())
                {
                    ++pointer;
                }
                else
                {
                    cout << "You have reached the end!" << endl;
                }
                break;
            case 2:
                if (pointer != needed_posts.begin())
                {
                    --pointer;
                }
                else
                {
                    cout << "There are no posts before this!" << endl;
                }
                break;
            case 3:
                // interact with post
                this->interact_post(*pointer);
                break;
            case 4:
                (*pointer)->displayCommentSection(this);
                break;
            case 5:
                return;
            default:
                break;
            }
        }
    }
    else
    {
        cout << "Here are the recommended posts. " << endl;
        auto curr_post_pointer = desired_posts.begin();

        if (!desired_posts.empty())
        {
            int ch;
            do
            {
                (*curr_post_pointer)->display_post_details();
                cout << "1. Next" << endl;
                cout << "2. Prev" << endl;
                cout << "3. Interact" << endl;
                cout << "4. Display Comment section" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice : ";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    if (curr_post_pointer + 1 != desired_posts.end())
                    {
                        ++curr_post_pointer;
                    }
                    else
                    {
                        cout << "You have reached the end!" << endl;
                    }
                    break;
                case 2:
                    if (curr_post_pointer != desired_posts.begin())
                    {
                        --curr_post_pointer;
                    }
                    else
                    {
                        cout << "There are no posts before this!" << endl;
                    }
                    break;
                case 3:
                    // interact
                    this->interact_post(*curr_post_pointer);
                    break;
                case 4:
                    (*curr_post_pointer)->displayCommentSection(this);
                    break;
                case 5:
                    return;
                default:
                    break;
                }
            } while (ch != 5);
        }
    }

    if (f1 && f)
    {
        if (allPosts.empty())
        {
            cout << "There are no posts in the system!" << endl;
        }
        else
        {
            auto final_pointer = allPosts.begin();
            int ch2;
            do
            {

                (*final_pointer)->display_post_details();
                cout << "1. Next" << endl;
                cout << "2. Prev" << endl;
                cout << "3. Interact" << endl;
                cout << "4. Display Comment Section" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice : ";
                cin >> ch2;
                switch (ch2)
                {
                case 1:
                    if (final_pointer + 1 != allPosts.end())
                    {
                        ++final_pointer;
                    }
                    else
                    {
                        cout << "You have reached the end!" << endl;
                    }
                    break;
                case 2:
                    if (final_pointer != allPosts.begin())
                    {
                        --final_pointer;
                    }
                    else
                    {
                        cout << "There are no posts before this!" << endl;
                    }
                    break;
                case 3:
                    this->interact_post(*final_pointer);
                    break;
                case 4:
                    (*final_pointer)->displayCommentSection(this);
                case 5:
                    return;
                default:
                    break;
                }
            } while (ch2 != 3);
        }
    }
}

Conversation *User::createDMConversation()
{
    cout << "Who do you wish to create a direct messaging conversation with?" << endl;
    vector<User> friends = findfriends(this);
    cout << "You have not engaged in a DM with these friends: " << endl;
    int i = 0;
    vector<User> selection;
    for (User u : friends)
    {
        Conversation *c = search_node(this->username, u.getUsername());
        if (!c)
        {
            cout << ++i << " . " << u.getUsername() << endl;
            selection.push_back(u);
        }
    }

    cout << "Select the user (their username ) (-1 to exit): ";

    string uname;
    cin >> uname;
    if (uname == "-1")
    {
        return nullptr;
    }
    Conversation *created_conv;
    bool flagdone = false;
    for (User &u : selection)
    {
        if (u.getUsername() == uname)
        {
            User *usr = new User(u);
            created_conv = new DMConversation(usr, this);
            store_conv(created_conv);
            flagdone = true;
            break;
        }
    }

    // testing
    // display_available_convs("naren");
    // testing
    if (flagdone)
    {
        cout << "DM successfully created" << endl;
        return created_conv;
    }
    else
    {
        cout << "Unable to form a conversation" << endl;
        return nullptr;
    }
}
Conversation *User::createCommunityConversation()
{

    cout << "Welcome to the community creation interface." << endl;
    cout << "Select the type of community you wish to create. " << endl;
    cout << "1. Request based community" << endl;
    cout << "2. Free join community" << endl;
    cout << "3. Exit" << endl;
    int choice = 0;
    Conversation *communityconv;
    do
    {
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            communityconv = new RequestBasedCommunity(this);
            break;
        case 2:
            communityconv = new FreeJoinCommunity(this);
            break;
        case 3:
            cout << "Exiting..";
            return nullptr;
            break;
        }
    } while (choice > 2);
    cout << endl
         << "Remember that with great power comes great responsibilities." << endl;
    cout << "Enter the name of your community: " << endl;
    string commname;
    getline(cin >> ws, commname);
    cout << endl
         << "Give a description about your community (helps us power our recommendation system): " << endl;
    string desp;
    getline(cin >> ws, desp);

    communityconv->setCommunityName(username, commname);
    communityconv->setCommunityDescription(username, desp);

    cout << endl
         << "You have succesfully created the community " << commname << endl;
    store_conv(communityconv);
    // display_available_convs(username);
    return communityconv;
}
vector<User> bfslevel(User *user, int level)
{
    vector<User> users;
    global_users->bfslevelutil(mui[user->getUsername()], users, level);
    return users;
}

void User::display_friend_suggestions()
{

    vector<User> suggestions = bfslevel(this, 2);
    int val = (suggestions.size() < 5) ? suggestions.size() : 5;
    cout << "Based on the analysis on your friends circle. Here are the top " << val << " friends we suggest " << endl;
    int i = 0;
    for (User &u : suggestions)
    {
        cout << ++i << " . " << u.getUsername() << endl;
        if (i == 5)
        {
            break;
        }
    }
    cout << "Who do you wish to be friends with (enter their username)? (-1 for exit) : ";
    string uname;
    getline(cin >> ws, uname);
    if (uname == "-1")
    {
        cout << "Exiting.." << endl;
        return;
    }
    for (User &u : suggestions)
    {
        if (u.getUsername() == uname)
        {
            this->addFriend(&u);
        }
    }
    cout << "Friend added successfully!" << endl;
}

bool valid_story(Story st)
{
    long t = st.time_of_creation;
    long current_time = time(NULL);

    if (current_time - t >= 860)
    {
        return false;
    } // change to 86400
    return true;
}

void User::displayStories()
{
    int ch;
    queue<Story> mystrs;
    for (auto &story : allstories)
    {
        for (auto &usr : story->to_be_shared_with)
        {
            if (usr.getUsername() == username)
            {
                mystrs.push(*story);
            }
        }
    }
    int csize = 0;
    cout << "Stories for " << username << endl;
    do
    {

        if (mystrs.size() != 0)
        {
           // csize++;

            // cout << my_stories.size() << endl;
            Story str = mystrs.front();
            //cout << str.sid << endl;
            mystrs.pop();
            if (valid_story(str))
            {
                for (auto sids : viewed_stories)
                {
                    if (sids == str.sid)
                    {
                        cout << "You already viewed this story" << endl;
                        break;
                    }
                }
                if (str.author->getUsername() == username)
                {
                    cout << "Your story " << endl;
                }
                mystrs.push(str);
                str.display();
                if (str.author->getUsername() != username)
                {
                    cout << "Like this story? (y/n): ";
                    char c;
                    cin >> c;
                    if (c == 'y')
                    {
                        bool f = true;
                        for (User *u : str.viewers)
                        {
                            if (u->getUsername() == username)
                            {
                                f = false;
                            }
                        }
                        if (f)
                        {
                            str.no_of_likes += 1;
                        }
                    }
                }
                str.viewers.insert(this);
                for (auto &s : allstories)
                {
                    //    / cout << s->sid << " " << str.sid << endl;
                    if (*s == str)
                    {
                        *s = str;
                    }
                }
                viewed_stories.push_back(str.sid);
            }
        }
        else
        {
            cout << "No  stories available" << endl;
            break;
        }
        cout << "1. Next story" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice " << endl;
        cin >> ch;
    } while (ch != 2);
}
void User::sendNotification(User *to, Conversation *forconv, string content)
{
    Notification *n = new Notification(content);
    n->setPriority(3 * time(NULL));
    n->setConversation(forconv);
    to->notifications.insert(*n);
}

void User::interact_post(Post *p)
{
    int ch;
    string con;
    string s_user;
    view_post(p);
    cout << "Interactions available:" << endl;
    cout << "1.Like Post\n2.Comment on post\n3.Share Post\n4.Exit\n"
         << endl;
    cout << "Choose your interaction:";
    cin >> ch;
    while (ch != 4)
    {
        if (ch == 1)
        {
            (*p) + this;
            break;
        }
        else if (ch == 2)
        {
            cout << "Enter the comment to post: ";
            getline(cin >> ws, con);
            Comment *msgcom = new Comment(this, con);
            p->addComment(msgcom);
            break;
        }
        else if (ch == 3)
        {
            Message *pm = new Message_Post(p);
            pm->setAuthor(this);
            int choiceforconvdisplay;
            cout << "Share with the following conversations" << endl;
            vector<Conversation *> available_conversations = display_available_convs(this->username);
            cout << "Enter your choice (0 to exit): ";
            cin >> choiceforconvdisplay;
            if (choiceforconvdisplay == 0)
            {
                return;
            }
            do
            {
                if (choiceforconvdisplay <= available_conversations.size())
                {
                    available_conversations[choiceforconvdisplay - 1]->sendMessage(pm);
                    p->no_of_shares++;
                    cout << "Post successfully shared!" << endl;
                }
                else
                {
                    cout << "Invalid option " << endl;
                }
            } while (choiceforconvdisplay > available_conversations.size());
            // cout<<"Enter the name of the user to send the post: ";
            // cin>>s_user;

            // User* t_user = search_user(s_user);
            // if (t_user == nullptr){
            //     cout<<"User not found\nExiting..\n"<<endl;
            //     return;
            // }else{
            //     this->share_post(&p,t_user);
            // }
        }
        else if (ch == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid option entered\nexiting..\n"
                 << endl;
            break;
        }
    }
}
#endif
