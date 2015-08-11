#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bs_tree.h"

Node *init_node(NODE *node, E data, int k)
{
    node->data = data;
    node->key = k;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
}

Node *tree_node(E data, int k)
{
    NODE *node;
    node = (NODE *)malloc(sizeof(NODE));
    return init_node(node, data, k);
}

Node *tree_search (NODE *x, int key)
{
    if(NULL == x || key == x->key)
        return x;
    else if(key < x->key)
        return tree_search(x->left, key);
    else
        return tree_search(x->right, key);
}

NODE *tree_minimum(NODE *x)
{
    while(x->left != NULL)
        x = x->left;
    return x;
}

NODE *tree_maximum(NODE *x)
{
    while(x->right != NULL)
        x = x->right;
    return x;
}

NODE *tree_successor(NODE *x)
{
    NODE *p;

    if(NULL != x->right)
        return tree_minimum(x->right);
    p = x->parent;
    while (p != NULL && p->right == x){
        x = p;
        p = x->parent;
    }
    return p;
}

NODE *tree_predecedor(NODE *x)
{
    NODE *p;
    if(NULL != x->left){
        return tree_maximum(x->left);
    }
    p=x->parent;
    while(NULL != p && p->left == x){
        x = p;
        p = x->parent;
    }
    return p;
}

NODE *tree_insert(ROOT *T, NODE *z)
{

    NODE *x = T, *y = NULL;
    while(NULL != x){
        y = x;
        if(x->key < z->key)
            x = x->right;
        else
            x = x->left;
    }
    if(NULL == y){    
        return z; // T == NULL;
    }
    else{
        z->parent = y;
        if(y->key < z->key)
            y->right = z;
        else
            y->left = z;
        return T;
    }
}

_Bool has_child(NODE *x)
{
    return (x != NULL) && (x->left != NULL || x->right != NULL)
}

NODE *swap_node(NODE *n1, NODE *n2)
{
    int tmp1;
    E tmp2;
    tmp1 = n1->key;
    tmp2 = n1->dat;
    n1->key = n2->key;
    n1->data = n2->data;
    n2->key = tmp1;
    n2->data = tmp2;
}

NODE *node_remove(ROOT *T, NODE *z)
{
    NODE *x;
    if(NULL == z->right){
        x = z->parent;
        if(x->left == z)
            x->left = z->left;
        else
            x->right = z->left;
        z->parent = NULL;
        z->left = NULL;
        return z;
    }
    else {
        x = tree_successor(z);
        swap_node(x,z);
        x->parent->left = x->right;
        x->parent = NULL;
        x->right = NULL;
        return x;
    }
}

NODE *tree_remove(ROOT *T, int k)
{
    NODE *z;
    z = tree_search(T, k);
    if(NULL != z)
        return node_remove(T, z);
    return z;
}
