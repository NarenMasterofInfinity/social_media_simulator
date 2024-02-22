#include "classes.h"
#include "user_methods.h"
#include <iostream>
#define MAX_SAVES 50
void User::operator+(Post* p){
    this->saved_posts[saved_ptr]= p;
    saved_ptr+=1;
}
string Post::getContent(){
    return content;
}
void User::show_saved_post(){
    for (int i=0; i<MAX_SAVES; i++){
        if(saved_posts[i]){
            cout<<saved_posts[i]->getContent()<<endl;
        }
    }
}

void display(User u){
    cout<<"username:"<<u.getUsername()<<endl;
    cout<<"email:"<<u.getEmail()<<endl;
}
void display(User u,bool b){
    
}
void Post::setContent(string content){
this->content = content;
}

int main(){
    cout<<"ADSFasf";
    User *u= new User("username","password","email");
    string content = "ADS LAB";
    Post *p = new Post(content,u);
    (*u)+p;
 //   cout<<p->getContent();
    u->show_saved_post();

}