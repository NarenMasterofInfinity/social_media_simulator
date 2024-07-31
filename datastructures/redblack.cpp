#include <iostream>

using namespace std;

class Node;


Node* nil = new Node(1001920912019009);
class Node{
    public:
        string color;
        Node *left,*right, *p;
        int key;
        Node(){}
        Node(int key){
            left = right = p = nil;
            this->key = key;
            color = "b";
        }
};

class RBTree{
    public:
        Node *root;
        void leftrotate(Node*);
};
int main(){}