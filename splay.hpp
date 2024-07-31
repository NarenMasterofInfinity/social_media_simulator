
#include "classes.hpp"


#ifndef SPLAY_H
#define SPLAY_H
template<typename T>
Snode<T> *SplayTree<T>::inorder_successor(Snode<T> *x)
{
    Snode<T> *y = x->right;
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
        (this->root)->val->create_interface();
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}
template<typename T>
Snode<T> *SplayTree<T>::zig(Snode<T> *node)
{
    Snode<T> *y = node->left;
    Snode<T> *Tx = y->right;
    Snode<T> *nP = node->p;
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
Snode<T> *SplayTree<T>::zag(Snode<T> *node)
{
    Snode<T> *y = node->right;
    Snode<T> *Tx = y->left;
    Snode<T> *nP = node->p;
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
void SplayTree<T>::splay_up(Snode<T> *node)
{
    if (!node)
    {
        return;
    }
    while (node != root)
    {
        Snode<T> *parent = node->p;
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
    Snode<T> *y = root;

    Snode<T> *x = y;
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
    Snode<T> *n = new Snode<T>(val);
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
    Snode<T> *x = nullptr;
    Snode<T> *y = root;
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

    Snode<T> *xP = x->p;
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
        Snode<T> *xr = x->right;
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
        Snode<T> *xl = x->left;
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
        Snode<T> *succ = inorder_successor(x);
        Snode<T> *succP = succ->p;
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
void SplayTree<T>::inorder(Snode<T> *node)
{
    if (!node)
    {
        return;
    }
    inorder(node->left);
    node->val->display();
    inorder(node->right);
}

#endif
