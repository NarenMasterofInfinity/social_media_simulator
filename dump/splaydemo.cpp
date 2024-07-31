#include "headers.hpp"
#include <iostream>

using namespace std;

int main()
{
    User *u1 = new User("naren", "naren@gmail.com", "naren3");
    User *u2 = new User("jan", "jan@gmail.com", "jan3");
    User *u3 = new User("jan3", "jan@gmail.com", "jan3");
    User *u4 = new User("nar1", "nar1@gmail.com", "naren3");
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for(User* &u : us){
        store_user(u);
    }


    Conversation *conv1 = new DMConversation(u1, u2);
    Conversation *conv2 = new DMConversation(u1, u3);
    Conversation *conv3 = new DMConversation(u3, u2);
    Conversation *conv4 = new DMConversation(u4, u5);
    Conversation *conv5 = new DMConversation(u5, u7);
    Conversation *conv6 = new DMConversation(u3, u6);
    Conversation *conv7 = new DMConversation(u5, u1);



    Conversation* cs[] = {conv1, conv2, conv3, conv4, conv5, conv6, conv7};

    for(Conversation*& c: cs){
        store_conv(c);
    }

    cout << "Here are the available conversations "<<endl;
     display_available_convs(u1->getUsername());

    int choice;

    cout  << "Select a conversation" <<endl;
    cin >> choice;

    vector<string> choices = available_choices[choice-1];


    //recent conversation is at the root.
    Conversation *chosen_conv = search_node(choices[0], choices[1]);

    chosen_conv->create_interface();

    cout << "The root of the tree is "<<endl;

    T.peekRoot();

}