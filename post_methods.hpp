#include "classes.hpp"
#include "user_methods.hpp"

#ifndef POST_H
#define POST_H

// void Post::display(){
//     cout << "=====================Post======================="<<endl;
//     cout << "By (" << author->getUsername()<<")" << endl;
//     cout << content << endl;
//     cout << "================================================"<<endl;
// }

// include #convs_db.hpp
//  void share_post(Post *p , User *receiver){
//      Conversation *c = search_node(username, receiver->getUsername());
//      Message *pm = new PostMessage(*p); //depending on the constructor;
//      pm->setAuthor(this);
//      c->sendMessage(pm);
//  }

void Post::EnterComment(User *commenter, bool reply)
{

    if (reply)
    {
        cout << "Enter the Comment ID: ";
        int cid;
        cin >> cid;
        cout << "Enter the Comment: ";
        string cont;
        getline(cin >> ws, cont);
        Comment *c = new Comment(commenter, cont);
        Comment *parentcomment = IntegerToComment[cid];

        addComment(c);
        Comments->addEdgeComment(parentcomment, c, this);
    }
    else
    {
        string con;
        cout << "Enter the Comment: ";
        getline(cin >> ws, con);
        Comment *cp = new Comment(commenter, con);
        addComment(cp);
    }
}

void Post::displayCommentSection(User *interactor)
{
    this->Comments->dfsComment(this);
    int choice;
    do
    {
        cout << "1. Reply to a comment\n2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            this->EnterComment(interactor, true);
            this->Comments->dfsComment(this);
            break;
        case 2:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 2);

    // /this->Comments->dfsComment(this);
}

void Post::display_post_details()
    {
        cout << "=======================Post====================" << endl;
        cout << endl;
        // cout << "Post ID: " << PID << endl;
        if(ptype == 1){
            post_image->display();
        }
        if(ptype == 2){
            post_video->display();
        }
        cout << "Content: " << content << endl;
        cout << "Author: " << author->getUsername() << endl;
        cout << "Likes: " << no_of_likes << endl;
        cout << "Shares: " << no_of_shares << endl;
        cout << endl
             << "===============================================" << endl;
    }

#endif