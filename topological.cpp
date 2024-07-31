#include "headers.hpp"

int main()
{
    User *u1 = new User("Sowndhar");
    User *u2 = new User("Naren");
    User *u3 = new User("Ravi");
    User *u4 = new User("Reddy");
    User *u5 = new User("Joe");
    User *u6 = new User("Ram");
    User *u7 = new User("Karthi");

    Comment *c1 = new Comment(u1, "Hi Im Sowndhar");
    usleep(50000);
    Comment *c2 = new Comment(u2, "Hi Im Naren");
    usleep(30000);
    Comment *c3 = new Comment(u3, "Hi Im Ravi");
    usleep(30000);
    Comment *c4 = new Comment(u4, "Hi Im Reddy");
    usleep(30000);
    Comment *c5 = new Comment(u5, "Hi Im Joe");
    usleep(30000);
    Comment *c6 = new Comment(u6, "Hi Im Ram");
    usleep(30000);
    Comment *c7 = new Comment(u7, "Hi Im karthi ");

    Comment *comm[] = {c1, c2, c3, c4, c5, c6, c7};

    Post *p = new Post("sample", u1);

    for (int i = 0; i < 7; i++)
    {
        p->addComment(comm[i]);
    }

    p->Comments->addEdgeComment(c1, c2, p);
    p->Comments->addEdgeComment(c1, c7, p);
    p->Comments->addEdgeComment(c2, c3, p);
    p->Comments->addEdgeComment(c2, c4, p);
    p->Comments->addEdgeComment(c2, c5, p);
    p->Comments->addEdgeComment(c3, c6, p);

    vector<Comment*> cs = p->Comments->topologicalSort(p);
    for(int i = 0; i < cs.size(); i++){
        cs[i]->display();
    }
}