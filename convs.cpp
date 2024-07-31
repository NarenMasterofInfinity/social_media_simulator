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
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for (int i = 0; i < 6; i++)
    {
        store_user(us[i]);
    }

    Conversation *conv1 = new DMConversation(u1, u2);
    Conversation *conv2 = new DMConversation(u1, u5);
    Conversation *conv3 = new DMConversation(u1, u7);
    CommunityConversation *cconv = new FreeJoinCommunity(u2);
    cconv->setCommunityName(u2->getUsername(), "Harry Potter");
    cconv->joinCommunity(u1);

    store_conv(conv1);
    store_conv(conv2);
    store_conv(conv3);
    store_conv(cconv);

    // bool status;
    // string username;
    // pair<bool, string> user_details = User::login();

    // status = user_details.first;
    // username = user_details.second;

    // vector<Conversation *> myconvs;

    // int convchoice;
    // if (status)
    // {
    //     myconvs = display_available_convs(username);
    //     int max_possible_choices = myconvs.size();
    //     cout << "Enter your choice : ";
    //     cin >> convchoice;
    //     Conversation *selected_conv = myconvs[convchoice - 1];
    //     selected_conv->create_interface();
    // }
    // else
    // {
    //     cout << "Try Again!" << endl;
    // }

    banner_display();
    bool running = true;
    while (running)
    {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "Enter your choice (type -1 to close): ";
        int register_login_choice;
        cin >> register_login_choice;

        switch (register_login_choice)
        {
        case 1:
            cout << "Registration will open soon!" << endl;
            break;
        case 2:
        {
            pair<bool, string> user_details = User::login();
            bool status = user_details.first;
            string username = user_details.second;
            User *loginuser;
            for (int i = 0; i < 6; i++)
            {
                if (us[i]->getUsername() == username)
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

            // Second level menu
            int display_conv_choice;
            do
            {
                cout << "1. Display my conversations" << endl;
                cout << "2. Back" << endl;
                cout << "Enter your choice: ";
                cin >> display_conv_choice;

                switch (display_conv_choice)
                {
                case 1:
                {
                    vector<Conversation *> myconvs;
                    myconvs = display_available_convs(username);
                    int max_possible_choices = myconvs.size();
                    if (max_possible_choices == 0)
                    {
                        cout << "No conversations available." << endl;
                        break;
                    }

                    int convchoice;
                    do
                    {
                        cout << "Enter your choice (-1 to go back): ";
                        cin >> convchoice;
                        if (convchoice == -1)
                        {
                            break;
                        }
                        if (convchoice > max_possible_choices || convchoice <= 0)
                        {
                            cout << "Please try again." << endl;
                        }
                        else
                        {
                            Conversation *selected_conv = myconvs[convchoice - 1];
                            selected_conv->create_interface();
                            int message_choice;
                            do
                            {
                                cout << "1. Send a Message" << endl;
                                cout << "2. Back" << endl;
                                cout << "Enter your choice: ";
                                cin >> message_choice;
                                Message *m1;
                                switch (message_choice)
                                {
                                case 1:
                                    m1 = prepare_message(loginuser);
                                    selected_conv->sendMessage(m1);
                                    selected_conv->create_interface();
                                    message_choice = 1;
                                    break;
                                case 2:
                                    message_choice = 1;
                                    break;
                                default:
                                    message_choice = 1;
                                    break;
                                }
                            } while (message_choice != 1);
                        }
                    } while (convchoice != -1);
                    break;
                }
                case 2:
                    // Back to previous menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            } while (display_conv_choice != 2);
            break;
        }
        case -1:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}