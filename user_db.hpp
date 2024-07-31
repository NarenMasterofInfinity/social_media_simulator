#include "classes.hpp"

#ifndef USER_DB_H
#define USER_DB_H

AVLTree<User> available_users;

void store_user(User *a)
{
    available_users.root = available_users.insert_node(available_users.root, *a);
    addUser(a);
    Similarity_Graph.addVertex(a);
}

void store_user(User a)
{
    available_users.root = available_users.insert_node(available_users.root, a);
    addUser(&a);
    Similarity_Graph.addVertex(&a);
}

void delete_user(User *a)
{
    // cout << "Entered";
    available_users.root = available_users.delete_node(available_users.root, *a);
}

void update_user(User *a)
{
    available_users.update_node(available_users.root, *a);
}
void update_user(User a)
{
    available_users.update_node(available_users.root, a);
}

vector<User> allusersearch(){
    vector<User> allusers;
    available_users.getusers(available_users.root, allusers);
    return allusers;
}
#endif