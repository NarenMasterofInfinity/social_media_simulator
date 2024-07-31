#include "headers.hpp"

int main()
{
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    Post *p1 = new Post("Example post 1 from " + u2->getUsername(), u2);
    Post *p2 = new Post("Example post 2 from " + u3->getUsername(), u3);
    Post *p3 = new Post("Example post 3 from " + u5->getUsername(), u5);
    Post *p4 = new Post("Example post 4 from " + u1->getUsername(), u1);
    Post *p5 = new Post("Example post 5 from " + u6->getUsername(), u6);
    Post *p6 = new Post("Example post 6 from " + u6->getUsername(), u6);
    Post *p7 = new Post("Example post 7 from " + u3->getUsername(), u3);
    Post *p8 = new Post("Example post 8 from " + u1->getUsername(), u1);
    Post *p9 = new Post("Example post 9 from " + u7->getUsername(), u7);
    Post *p10 = new Post("Example post 10 from " + u5->getUsername(), u5);
    Post *p11 = new Post("Example post 11 from " + u5->getUsername(), u5);

    Post *ps[] = {p1, p2, p3, p4, p5, p6};

    int i = explanationPostPtr;

    ExplanationPost.resize(i + 1);
    ExplanationPost[i] = new Graph();
    for (int j = 0; j < 6; j++)
    {
        ExplanationPost[i]->addPostVertex(i, ps[j]);
    }
    ExplanationPost[i]->addPostEdge(i, p1, p2);
    ExplanationPost[i]->addPostEdge(i, p1, p3);
    ExplanationPost[i]->addPostEdge(i, p1, p4);
    ExplanationPost[i]->addPostEdge(i, p2, p5);
    ExplanationPost[i]->addPostEdge(i, p3, p6);
    ExplanationPost[i]->addPostEdge(i, p4, p6);
    vector<Post *> posts = ExplanationPost[i]->topologicalSortForPost(i);
    for (int f = 0; f < posts.size(); f++)
    {
        posts[f]->display();
    }
    explanationPostPtr++;
}