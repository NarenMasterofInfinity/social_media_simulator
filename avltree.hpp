#include "classes.hpp"

using namespace std;

#ifndef AVL_H
#define AVL_H
template <typename T>
Node<T> *AVLTree<T>::minimum(Node<T> *root)
{
    if (!root)
        return nullptr;
    if (root->left == nullptr)
        return root;
    return minimum(root->left);
}
template <typename T>
void update_heights(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    update_heights(root->left);
    update_heights(root->right);
    update_height(root);
}
template <typename T>
void update_height(Node<T> *root)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr)
    {
        root->height = 1;
        return;
    }
    if (root->left == nullptr)
    {
        root->height = 1 + root->right->height;
        return;
    }
    if (root->right == nullptr)
    {
        root->height = 1 + root->left->height;
        return;
    }
    else
    {
        root->height = 1 + max(root->right->height, root->left->height);
    }
}
template <typename T>
Node<T> *AVLTree<T>::parent(Node<T> *root, Node<T> *node)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->left == node)
    {
        return root;
    }
    if (root->right == node)
    {
        return root;
    }
    Node<T> *p = parent(root->right, node);
    Node<T> *q = parent(root->left, node);
    if (!(p || q))
    {
        return nullptr;
    }
    if (!p)
    {
        return q;
    }
    else
    {
        return p;
    }
}

template <typename T>
Node<T> *AVLTree<T>::search(Node<T> *root, T data)
{

    if (root == nullptr)
    {
        return root;
    }

    // cout << root->val.getUsername() << endl;
    if ((data == (root->val)))
    {

        return root;
    }
    if ((data > (root->val)))
    {
        return search(root->right, data);
    }
    else
    {
        return search(root->left, data);
    }
    // cout << (data == nullptr);
    return root;
}

template <typename T>
Node<T> *AVLTree<T>::left_rotate(Node<T> *node)
{
    Node<T> *p = parent(root, node);

    if (p == nullptr)
    {
        this->root = node->right;
        node->right = this->root->left;
        this->root->left = node;
        return this->root;
    }
    if (p->left == node)
    {
        p->left = node->right;
        node->right = p->left->left;
        p->left->left = node;
        return p->left;
    }
    else
    {
        p->right = node->right;
        node->right = p->right->left;
        p->right->left = node;
        return p->right;
    }
}

template <typename T>
void AVLTree<T>::inorder(Node<T> *node)
{
    if (node == nullptr)
        return;
    inorder(node->left);
    (node->val)->display();
    inorder(node->right);
}

template <typename T>
Node<T> *AVLTree<T>::right_rotate(Node<T> *node)
{
    Node<T> *p = parent(root, node);
    if (p == nullptr)
    {
        this->root = node->left;
        node->left = this->root->right;
        this->root->right = node;
        return this->root;
    }
    if (p->left == node)
    {
        p->left = node->left;
        node->left = p->left->right;
        p->left->right = node;
        return p->left;
    }
    else
    {
        p->right = node->left;
        node->left = p->right->right;
        p->right->right = node;
        return p->right;
    }
}

template <typename T>
Node<T> *AVLTree<T>::insert_node(Node<T> *node, T data)
{
    if (node == nullptr)
    {
        Node<T> *n = new Node<T>(data);
        return n;
    }
    else if (node->val < data) // pointer change
    {
        node->right = insert_node(node->right, data);
    }
    else
    {
        node->left = insert_node(node->left, data);
    }
    update_heights(node);

    if ((find_balance(node) > 1) && (find_balance(node->left) > 0))
    {
        node = this->right_rotate(node);
    }
    else if (find_balance(node) > 1)
    {
        node->left = this->left_rotate(node->left);
        node = this->right_rotate(node);
    }
    else if (find_balance(node) < -1 && find_balance(node->right) < 0)
    {
        node = this->left_rotate(node);
    }
    else if (find_balance(node) < -1)
    {
        node->right = this->right_rotate(node->right);
        node = this->left_rotate(node);
    }
    update_heights(this->root);
    return node;
}

template <typename T>
int find_balance(Node<T> *root)
{

    if (root == nullptr)
    {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        return 0;
    }
    if (root->right == nullptr)
    {
        return root->left->height;
    }
    if (root->left == nullptr)
    {
        return 0 - root->right->height;
    }
    return (root->left->height - root->right->height);
}

template <typename T>
int AVLTree<T>::size(Node<T> *x)
{
    int c = 0;
    if (x == nullptr)
    {
        return 0;
    }
    c += size(x->left);
    c += size(x->right);
    return c + 1;
}

template <typename T>
void AVLTree<T>::inorder_no_pointer(Node<T> *node)
{
    if (node)
    {
        this->inorder_no_pointer(node->left);
        (node->val).display();
        this->inorder_no_pointer(node->right);
    }
}
template <typename T>
void AVLTree<T>::update_node(Node<T> *root, T val)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->val == val)
    {
        root->val = val;
        return;
    }
    else if (root->val > val)
    {
        update_node(root->left, val);
    }
    else
    {
        update_node(root->right, val);
    }
    return;
}
template <typename T>
Node<T> *AVLTree<T>::delete_node(Node<T> *root, T val)
{

    Node<T> *snode = search(root, val);
    Node<T> *spnode = parent(root, snode);
    bool l, r;
    r = l = false;
    if (snode == nullptr)
    {
        return nullptr;
    }
    else if (spnode != nullptr)
    {
        if (spnode->left == snode)
        {
            l = true;
        }
        else
        {
            r = true;
        }
    }
    // no children
    if (!(snode->left || snode->right))
    {
        if (!spnode)
            this->root = snode;
        if (l)
            spnode->left = nullptr;
        if (r)
            spnode->right = nullptr;
        // delete snode;
    }
    // one child
    // left child exists
    else if (!(snode->right))
    {
        snode = snode->left;
        if (l)
            spnode->left = snode;
        if (r)
            spnode->right = snode;
        else
            this->root = snode;
    }
    else if (!(snode->left))
    {
        snode = snode->right;
        if (l)
            spnode->left = snode;
        if (r)
            spnode->right = snode;
        else
            this->root = snode;
    }
    else
    {
        Node<T> *succ = minimum(snode->right);
        Node<T> *succP = parent(root, succ);

        if (succP->left == succ)
            succP->left = succ->right;
        else
            succP->right = succ->right;
        snode->val = succ->val;
    }
    update_heights(root);
    while (snode != nullptr)
    {
        if ((find_balance(snode) > 1) && (find_balance(snode->left) > 0))
        {
            snode = this->right_rotate(snode);
        }
        else if (find_balance(snode) > 1)
        {
            snode->left = this->left_rotate(snode->left);
            snode = this->right_rotate(snode);
        }
        else if (find_balance(snode) < -1 && find_balance(snode->right) < 0)
        {
            snode = this->left_rotate(snode);
        }
        else if (find_balance(snode) < -1)
        {
            snode->right = this->right_rotate(snode->right);
            snode = this->left_rotate(snode);
        }
        update_heights(root);
        snode = parent(root, snode);
    }

    return root;
}
template <class T>
void AVLTree<T>::getmsgs(Node<T> *root, list<Message*>& allmsgs)
{
    if(root == nullptr){
        return;
    }
    allmsgs.push_back(root->val);
    getmsgs(root->left, allmsgs);
    getmsgs(root->right, allmsgs);
}
template <class T>
void AVLTree<T>::getusers(Node<T> *root, vector<User>& allusers)
{
    if(root == nullptr){
        return;
    }
    allusers.push_back(root->val);
    getusers(root->left, allusers);
    getusers(root->right, allusers);
}
#endif
