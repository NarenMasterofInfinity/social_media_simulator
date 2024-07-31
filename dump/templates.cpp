#include <iostream>
#include "classes.hpp"
#include "multimedia_methods.hpp"
#include "text_methods.hpp"
#include "str_emoji_methods.hpp"
#include "user_db.hpp"
#include "conv_dm.hpp"
#include "user_methods.hpp"

int main(){
    User *u1 = new User("naren","naren@gmail.com","naren3");
    User *u2 = new User("jan","jan@gmail.com","jan3");

    cout<<"Difference between normal and emojified text: "<<endl;
    cout<<"Enter a string: ";
    string content;
    getline(cin>>ws, content);

    Text<String> t1(content);
    Text<Emoji> t2(content);

    cout<<"Normal : "<<t1.getContent()<<endl;
    cout << "Emojified : "<<t2.getContent()<<endl;

    store_user(u1);
    store_user(u2);

    DMConversation *conv = new DMConversation(u1,u2);

    store_conv(conv);

    // (*u1) > (*u2);

    conv->sendText<Image>(u1);
    conv->sendText<Video>(u1);
    conv->sendText<Audio>(u2);

    conv->sendText<Text<Emoji>>(u2);

    conv->create_interface();

}