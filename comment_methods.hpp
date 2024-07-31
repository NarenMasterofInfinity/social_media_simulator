#include "classes.hpp"

#ifndef COMMENT
#define COMMENT
string time_elapsed(long t)
{
    int diff = time(NULL) - t;
    string res = "";
    res += "(";
    if (diff > 60 && diff < 3600)
    {
        res += to_string((diff / 60)) + " minutes ago";
    }
    else if (diff > 60 && diff < 86400)
    {
        res += to_string(diff / 3600) + " hours ago";
    }
    else if (diff > 60)
    {
        res += to_string(diff / 86400) + " days ago";
    }
    else
    {
        res += to_string(diff) + " seconds ago";
    }
    res += ")";
    return res;
}
void printIndentation(int level)
{
    for (int i = 0; i < level; i++)
    {
        cout << "    ";
    }
}

void printHorizontalLine(int level)
{
    printIndentation(level);
    cout << "+-----------------------------------+" << endl;
}

void Comment::DisplayComment(int level, Post *p)
{

    printHorizontalLine(level);

    int comment_id = p->CommentToInteger[this];

    printIndentation(level);
    cout << "| Comment ID: " << comment_id << endl;

    printIndentation(level);
    cout << "| @" << author->getUsername() <<" " << time_elapsed(time_of_creation)<< endl;
    printIndentation(level);
    cout << "| ";

    // /printIndentation(level);
    cout << content << endl;

    // if (hasReplies()) {
    //     printIndentation(level);
    //     cout << "| Replies:" << endl;
    // }

    printHorizontalLine(level);
    cout << endl;
}

void Comment::display()
{

    cout << "====================================" << endl;
    string s = "";

    s += author->getUsername();
    s += time_elapsed(time_of_creation);
    s += "\n";

    cout << s << content << endl;

    cout << "====================================";
    cout << endl;
}

#endif