#include "classes.hpp"
#include <string>

#ifndef TEXT_METHODS_H
#define TEXT_METHODS_H

template<typename T>
User* Text<T>::getAuthor(){
    return author;
}
template<typename T>
string Text<T>::getContent(){
    return content.getContent();
}
template<typename T>
void Text<T>::setAuthor(User *user){
    author = user;
}
template<typename T>
void Text<T>::setContent(string content){
    this->content = content;
}
template<typename T>
void Text<T>::display(){
    cout<< author->getUsername() <<" : ";
    content.display();
}

template<typename T>
string Text<T>::getType(){
    return TEXT_MSG;
}

#endif