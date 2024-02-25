#include <iostream>
#include "classes.hpp"
#include "user_methods.hpp"
#include "conv_methods.hpp"
#include "conv_dm.hpp"
#include "text_methods.hpp"
#include "group_methods.hpp"
#include "user_db.hpp"
#include "conv_community.hpp"

int main()
{

    // Defining some users
    string username1 = "Naren";
    string username2 = "Aadharsh";
    string username3 = "Harini";
    string username4 = "Sowndhar";
    string username5 = "Prasanna";
    string username6 = "Yuvashri";
    string username7 = "Navin";

    // emails
    string email1 = "Naren@gmail.com";
    string email2 = "Aadharsh@gmail.com";
    string email3 = "Harini@gmail.com";
    string email4 = "Sowndhar@gmail.com";
    string email5 = "Prasanna@gmail.com";
    string email6 = "Yuvashri@gmail.com";
    string email7 = "Navin@gmail.com";

    // passwords
    string pass1 = "afasfdsfsadf34";
    string pass2 = "sadflj33";
    string pass3 = "asdf3rarf";
    string pass4 = "adfjaei";
    string pass5 = "sdajfna3i";
    string pass6 = "jlafo3";
    string pass7 = "jakfhdo3";

    // creating user objects

    User *u1 = new User(username1, email1, pass1);
    User *u2 = new User(username2, email2, pass2);
    User *u3 = new User(username3, email3, pass3);
    User *u4 = new User(username4, email4, pass4);
    User *u5 = new User(username5, email5, pass5);
    User *u6 = new User(username6, email6, pass6);
    User *u7 = new User(username7, email7, pass7);

    store_user(u1);
    store_user(u2);
    store_user(u3);
    store_user(u4);
    store_user(u5);
    store_user(u6);
    store_user(u7);

    Message *msg1 = new Text();
    Message *msg2 = new Text();
    Message *msg3 = new Text();

    Conversation *conv = new DMConversation(u1, u2);

    msg1->setAuthor(u2);
    msg1->setContent("This is my first message");

    // direct Conversations
    conv->sendText(u1);
    conv->sendText(u2);

    conv->create_interface();

    cout << endl
         << endl
         << endl
         << endl;

    cout << "Group Conversation" << endl;

    conv = new GroupConversation(u3, "Team_4");

    conv->add_participants(5);
    conv->sendMessage(msg1);

    msg2->setAuthor(u3);
    msg2->setContent("This is the second message");
    conv->sendMessage(msg2);

    msg3->setAuthor(u5);
    msg3->setContent("This is the third message");
    conv->sendMessage(msg3);

    conv->create_interface();

    cout << endl
         << endl
         << endl;

    cout << "Community conversation" << endl;

    CommunityConversation *req_conv = new RequestBasedCommunity(u5);
    req_conv->setCommunityName(u5->getUsername(),"Birds");
    req_conv->setCommunityDescription(u5->getUsername(),"This is a thriving community on birds!");

    cout << "Accessing as non-admin:" << endl;
    req_conv->addMembers(u3->getUsername(),3);
    cout<<endl;
    cout << "With admin priveleges" << endl;
    req_conv->addMembers(u5->getUsername(),3);

    cout<<"Sending request.."<<endl;
    req_conv->issueRequest(u2);

    cout<<endl;
    //u5 is the admin
    req_conv->acceptRequest(u5);

    req_conv->display_participants();

    //sending message as non-admin

    Message *msg5 = new Text();
    msg5->setAuthor(u2);
    msg5->setContent("This is a community message");

    cout<<"Sending message as non-admin"<<endl;
    req_conv->sendMessage(msg5);

    cout<<"Sending message as admin"<<endl;
    msg5->setAuthor(u5);
    req_conv->sendMessage(msg5);

    req_conv->create_interface();

    //u7 is the admin
    CommunityConversation* free_conv = new FreeJoinCommunity(u7);
    free_conv->addMembers(2);

    //u1 issues a join
    free_conv->joinCommunity(u1);

    free_conv->display_participants();
    return 0;
}