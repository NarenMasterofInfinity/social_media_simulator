#include "headers.hpp"

using namespace std;

int main()
{
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    Message *m1 = new Text<String>("Hi! how are you");
    Message *m2 = new Image("path.jpg");
    Message *m3 = new Audio("path.wav");
    Message *m4 = new Video("path.mpe4");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for (User *&u : us)
    {
        store_user(u);
    }

    m1->setAuthor(u2);
    m2->setAuthor(u2);
    m3->setAuthor(u2);
    m4->setAuthor(u2);

    Conversation *conv = new DMConversation(u4, u2);
    CommunityConversation *fconv = new FreeJoinCommunity(u2);

    fconv->setCommunityName(u2->getUsername(), "Birds & Science");

    store_conv(conv);
    store_conv(fconv);

    pair<bool, string> pu = User::login();

    fconv->joinCommunity(u4);

    conv->sendMessage(m1);

    conv->sendMessage(m3);

    fconv->sendMessage(m2);
    fconv->sendMessage(m4);

    cout << "Want to see your notifications? (y/n)" << endl;

    char choice;
    cin >> choice;

    if (choice == 'y')
    {
        if (pu.first)
        {
            for (User *u : us)
            {
                if (u->getUsername() == pu.second)
                {
                    u->displayNotifications();
                    cout << "Select a notification ";
                    int i;
                    cin >> i;

                    Notification n = u->notifications.search(i);
                    Conversation *conv_of_interest = n.belongs_to;
                    conv_of_interest->create_interface();
                    cout << "Do you wish to send a message? (y/n)";
                    cin >> choice;
                    if (choice != 'y'){
                        break;
                    }
                    Message *m = prepare_message(u);
        
                    conv_of_interest->sendMessage(m);
                    conv_of_interest->create_interface();
                        break;
                }
            }
        }
    }
    else
    {
        cout << "Bye.." << endl;
    }
}
