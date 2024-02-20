#include "classes.h"

#ifndef TEXT_METHODS_H
#define TEXT_METHODS_H

User* Text::getAuthor(){
    return author;
}

string Text::getContent(){
    return content;
}

void Text::setAuthor(User *user){
    author = user;
}

void Text::setContent(string content){
    this->content = content;
}

#endif