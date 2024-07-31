#include "classes.hpp"
#include <vector>

#ifndef CONV_DB_H
#define CONV_DB_H

SplayTree<Conversation *> T;
vector<vector<string>> available_choices;
int cc = 0;

double countutil(string user1, string user2, Snode<Conversation *> *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    Conversation *temp = root->val;
    int c = 0;
    double jk = 0;
    string holder = "";
    for (User *u : temp->participants)
    {
        if (c == 0)
        {
            string utemp = u->getUsername();

            if (utemp == user1)
            {

                holder = user2;
                c += 1;
            }
            if (utemp == user2)
            {
                holder = user1;
                c += 1;
            }
        }
        else if (c == 1)
        {
            string utemp1 = u->getUsername();
            if (utemp1 == holder)
            {
                c += 1;
                jk = 1 * (temp->priority);
            }
        }
        else
        {
            jk = 1 * (temp->priority);
            break;
        }
    }

    jk += countutil(user1, user2, root->left);
    jk += countutil(user1, user2, root->right);
    return jk;
}

Snode<Conversation *> *search(string user1, string user2, bool comm, Snode<Conversation *> *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Conversation *temp = root->val;
    int c = 0;
    string holder = "";
    for (User *u : temp->participants)
    {
        if (c == 0)
        {
            string utemp = u->getUsername();
            if (utemp == user1)
            {
                holder = user2;
                c += 1;
            }
            if (utemp == user2)
            {
                holder = user1;
                c += 1;
            }
        }
        else if (c == 1)
        {
            string utemp1 = u->getUsername();
            if (utemp1 == holder)
            {
                c += 2;
            }
        }
        else
        {
            cc += 1;
            break;
        }
    }

    Snode<Conversation *> *lnode = search(user1, user2, true, root->left);
    Snode<Conversation *> *rnode = search(user1, user2, true, root->right);
    return (lnode == nullptr) ? lnode : rnode;
}

Conversation *search_node(string user1, string user2, bool comm)
{
    Snode<Conversation *> *s = search(user1, user2, true, T.root);
    return (s == nullptr) ? nullptr : s->val;
}

double count_convs(string user1, string user2)
{
    double c = countutil(user1, user2, T.root);
    return c;
}

Snode<Conversation *> *search(string user1, string user2, Snode<Conversation *> *root)
{

    if (root == nullptr)
    {
        return nullptr;
    }
    if ((root->val)->participants.size() < 2)
    {
        return nullptr;
    }
    string xuser1 = ((root->val)->participants[0])->getUsername();
    string xuser2 = ((root->val)->participants[1])->getUsername();

    if ((xuser1 == user1 || xuser2 == user1) && (xuser1 == user2 || xuser2 == user2))
    {
        T.splay_up(root);
        return root;
    }

    Snode<Conversation *> *lnode = search(user1, user2, root->left);
    Snode<Conversation *> *rnode = search(user1, user2, root->right);

    return (lnode == nullptr) ? rnode : lnode;
}

Conversation *search_node(string user1, string user2)
{
    Snode<Conversation *> *s = search(user1, user2, T.root);
    if (s != nullptr)
    {
        return s->val;
    }
    return nullptr;
}

void store_conv(Conversation *a)
{
    T.insert_node(a);
    if (a->priority < 1.74)
    {
        Community_Graph.addVertex(a);
    }
}

void display_available_convs_util(string username, Snode<Conversation *> *root, vector<Conversation *> &allconvs, int &count)
{

    if (!root)
    {
        return;
    }

    Snode<Conversation *> *thisnode = root;

    for (User *u : (thisnode->val)->participants)
    {
        if (!u)
        {
            break;
        }
        if (u->getUsername() == username)
        {
            if (thisnode->val->priority == 2)
            {
                cout << ++count << ". Conversation among" << endl;
                allconvs.push_back(thisnode->val);
                int i = 0;
                vector<string> s;
                for (User *u : (thisnode->val)->participants)
                {
                    if (!u)
                    {
                        break;
                    }
                    s.push_back(u->getUsername());
                    cout << char('a' - 1 + ++i) << ". " << u->getUsername() << endl;
                }
                available_choices.push_back(s);
                break;
            }
            else if (thisnode->val->priority != 1.75)
            {
                if (thisnode->val->priority == 1)
                {
                    cout << ++count << ". Community : " << thisnode->val->getCommunityName() << " (Free to Join) " << endl;
                }
                else
                {
                    cout << ++count << ". Community : " << thisnode->val->getCommunityName() << " (Requires approval from the admin)"<< endl;
                }
                allconvs.push_back(thisnode->val);
                break;
            }
            else
            {
                cout << ++count << ". Group : " << thisnode->val->getGroupName() << endl;
                allconvs.push_back(thisnode->val);
                break;
            }
        }
    }
    display_available_convs_util(username, root->left, allconvs, count);
    display_available_convs_util(username, root->right, allconvs, count);
}

void available_convs_util(string username, Snode<Conversation *> *root, vector<Conversation *> &allconvs)
{

    if (!root)
    {
        return;
    }

    Snode<Conversation *> *thisnode = root;

    for (User *u : (thisnode->val)->participants)
    {
        if (!u)
        {
            break;
        }
        if (u->getUsername() == username)
        {
            if (thisnode->val->priority == 2)
            {

                allconvs.push_back(thisnode->val);
                int i = 0;
                vector<string> s;
                for (User *u : (thisnode->val)->participants)
                {
                    if (!u)
                    {
                        break;
                    }
                    s.push_back(u->getUsername());
                }
                available_choices.push_back(s);
                break;
            }
            else
            {

                allconvs.push_back(thisnode->val);
                break;
            }
        }
    }
    available_convs_util(username, root->left, allconvs);
    available_convs_util(username, root->right, allconvs);
}

vector<Conversation *> available_convs(string username)
{
    vector<Conversation *> allconvs;
    available_convs_util(username, T.root, allconvs);
    return allconvs;
}

vector<Conversation *> display_available_convs(string username)
{
    vector<Conversation *> allconvs;
    int count = 0;
    display_available_convs_util(username, T.root, allconvs, count);
    return allconvs;
}

void displayRBCommutil(string username, Snode<Conversation *> *root, vector<Conversation *> &allconvs, int &count)
{
    if (!root)
    {
        return;
    }

    Snode<Conversation *> *thisnode = root;

    for (User *u : (thisnode->val)->participants)
    {
        if (!u)
        {
            break;
        }
        if (u->getUsername() == username)
        {
            if (thisnode->val->priority == 1.5)
            {
                cout << ++count << " . Community: " << thisnode->val->getCommunityName() << endl;
                allconvs.push_back(thisnode->val);
                break;
            }
        }
    }
    displayRBCommutil(username, root->left, allconvs, count);
    displayRBCommutil(username, root->right, allconvs, count);
}
vector<Conversation *> displayRBCommunities(string username)
{
    vector<Conversation *> allconvs;
    int count = 0;
    displayRBCommutil(username, T.root, allconvs, count);
    return allconvs;
}
void getallcommsutil(Snode<Conversation *> *root, vector<Conversation*> &allavailconvs){
    if(root == nullptr){
        return;
    }
    if(root->val->priority == 1 || root->val->priority == 1.5){
        allavailconvs.push_back(root->val);
    }
    getallcommsutil(root->left, allavailconvs);
    getallcommsutil(root->right, allavailconvs);
}
vector<Conversation*> getallcomms(){
    vector<Conversation*> allavailconvs;
    getallcommsutil(T.root, allavailconvs);
    return allavailconvs;
}
#endif