#include <iostream>

using namespace std;

template<typename T>
class Node;
template<typename T>
class SplayTree;


template<typename T>
class Node
{
public:
    Node<T> *right, *left, *p;
    T val;
    Node()
    {
        right = left = p = nullptr;
    }
    Node(T val)
    {
        this->val = val;
        right = left = p = nullptr;
    };
};

template<typename T>
class SplayTree
{
public:
    Node<T> *root;
    SplayTree()
    {
        root = nullptr;
    };
    void insert_node(T);
    void left_rotate(Node<T> *);
    void right_rotate(Node<T> *);
    void inorder(Node<T> *);
    void splay_up(Node<T> *);
    Node<T> *zig(Node<T> *);
    Node<T> *zag(Node<T> *);
    Node<T> *inorder_successor(Node<T> *);
    void delete_node(T);
    void peekRoot();
};

template<typename T>
Node<T> *SplayTree<T>::inorder_successor(Node<T> *x)
{
    Node<T> *y = x->right;
    while (y != nullptr)
    {
        y = y->left;
    }
    return y;
}
template<typename T>
void SplayTree<T>::peekRoot()
{
    if (root)
    {
        cout << endl << "Root is " << root->val << endl;
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}
template<typename T>
Node<T> *SplayTree<T>::zig(Node<T> *node)
{
    Node<T> *y = node->left;
    Node<T> *Tx = y->right;
    Node<T> *nP = node->p;
    if (nP == nullptr)
    {
        root = y;
        y->right = node;
        node->left = Tx;
    }
    else
    {
        int pos = (nP->left == node) ? 1 : 0;
        if (pos)
            nP->left = y;
        else
            nP->right = y;
        y->right = node;
        node->left = Tx;
    }
    if (Tx)
        Tx->p = node;
    if (y)
        y->p = nP;
    node->p = y;
    return node;
}
template<typename T>
Node<T> *SplayTree<T>::zag(Node<T> *node)
{
    Node<T> *y = node->right;
    Node<T> *Tx = y->left;
    Node<T> *nP = node->p;
    if (nP == nullptr)
    {
        root = y;
        y->left = node;
        node->right = Tx;
    }
    else
    {
        int pos = (nP->left == node) ? 1 : 0;
        if (pos)
            nP->left = y;
        else
            nP->right = y;
        y->left = node;
        node->right = Tx;
    }
    if (Tx)
        Tx->p = node;
    if (y)
        y->p = nP;
    node->p = y;
    return node;
}
template<typename T>
void SplayTree<T>::splay_up(Node<T> *node)
{
    if (!node)
    {
        return;
    }
    while (node != root)
    {
        Node<T> *parent = node->p;
        int pos = (node == parent->left) ? 1 : 0;
        if (pos)
            node = zig(parent);
        else
            node = zag(parent);
        node = node->p;
    }
}
template<typename T>
void SplayTree<T>::insert_node(T val)
{
    Node<T> *y = root;

    Node<T> *x = y;
    while (y != nullptr)
    {
        x = y;
        if (y->val < val)
        {
            y = y->right;
        }
        else
        {
            y = y->left;
        }
    }
    Node<T> *n = new Node(val);
    n->p = x;
    if (!x)
    {
        root = n;
    }
    else if (x->val > val)
    {
        x->left = n;
    }
    else
    {
        x->right = n;
    }

    splay_up(n);
}
template<typename T>
void SplayTree<T>::delete_node(T val)
{
    Node<T> *x = nullptr;
    Node<T> *y = root;
    while (y != nullptr)
    {
        if (val > y->val)
        {
            y = y->right;
        }
        else if (val < y->val)
        {
            y = y->left;
        }
        else
        {
            x = y;
            break;
        }
    }

    Node<T> *xP = x->p;
    int pos = -1;
    if (xP)
    {
        pos = (xP->left == x) ? 1 : 0;
    }
    // no children
    if (x->left == nullptr && x->right == nullptr)
    {
        if (!xP)
        {
            root = nullptr;
            return;
        }
        if (pos)
            xP->left = nullptr;
        else
            xP->right = nullptr;
        splay_up(xP);
        return;
    }

    // one child
    if (x->left == nullptr)
    {
        Node<T> *xr = x->right;
        if (!xP)
        {
            root = xr;
            return;
        }
        if (pos)
            xP->left = xr;
        else
            xP->right = xr;

        xr->p = xP;

        splay_up(xr);
        return;
    }
    else if (x->right == nullptr)
    {
        Node<T> *xl = x->left;
        if (!xl)
        {
            root = xl;
            return;
        }
        if (pos)
            xP->left = xl;
        else
            xP->right = xl;
        xl->p = xP;
        splay_up(xl);
        return;
    }
    // two children here
    else
    {
        Node<T> *succ = inorder_successor(x);
        Node<T> *succP = succ->p;
        if (!xP)
        {
            root = succ;
        }
        else
        {
            if (!pos)
                xP->right = succ;
            else
                xP->left = succ;
        }
        if (succP->right == succ)
        {
            succ->p = xP;
        }
        else
        {
            succP->left = x->right;
            if (x->right)
                x->right->p = succP;
            succ->p = xP;
        }

        splay_up(succ);
        return;
    }
}
template<typename T>
void SplayTree<T>::inorder(Node<T> *node)
{
    if (!node)
    {
        return;
    }
    inorder(node->left);
    cout << node->val << " ";
    inorder(node->right);
}

int main()
{
    SplayTree<int> T;
    T.insert_node(10);
    T.insert_node(50);
    T.insert_node(5);
    T.insert_node(23);
    T.insert_node(41);
    T.insert_node(2);
    cout << "Before deletion" << endl;
    T.inorder(T.root);

    cout << endl
         << "After deletion " << endl;
    T.delete_node(2);
    T.inorder(T.root);
    T.peekRoot();
}