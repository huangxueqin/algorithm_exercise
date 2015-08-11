#include <stdio.h>
#include "red_black_tree.h"

NODE *nil = {
    .key = 0,
    .color = BLACK,
    .parent = nil,
    .left = nil,
    .right = nil,
};

static inline _Bool isRoot (NODE *z)
{
    return z->parent == nil;
}

NODE *makeRoot (NODE *z)
{
    z->color = BLACK;
    z->parent = nil;
    z->left = nil;
    z->right = nil;
    return z;
}

void left_rotate (RBTree *T, NODE *x)
{
    NODE *y = x->right;
    y->parent = x->parent;
    x->parent = y;
    y->left->parent = x;
    x->right = y->left;
    y->left = x;
    if(y->parent != nil) {
        if(y->parent->key > y->key)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
}

void right_rotate (RBTree *T, NODE *x)
{
    NODE *y = x->left;
    y->parent = x->parent;
    x->parent = y;
    y->right->parent = x;
    x->left = y->right;
    y->right = x;
    if(y->parent != nil) {
        if(y->parent->key > y->key)
            y->parent->left = y;
        else
            y->parent->right = y;
    }

}

RBTree *RB_insert_fixup(RBTree *T, NODE *z)
{
    while(z->parent->color != BLACK) {
        NODE *p = z->parent;
        NODE *p2 = p->parent->left == p ? p->parent->right : p->parent->left;
        if(p2->color == RED){
            p2->color = BLACK;
            p->color = BLACK;
            p->parent->color = RED;
            z = p->parent;
        }
        else {
            NODE *pp = p->parent;
            if(p->parent->left == p) {
                if(z == p->right)
                    left_rotate(T, p);
                right_rotate(T, pp);
            }
            else {
                if(z == p->left)
                    right_rotate(T, p);
                left_rotate(T, pp);
            }
            pp->color = BLACK;
            pp->parent->color = RED;
            z->color = BLACK;
            z = pp->parent;
        }
    }
    if(isRoot(z)){
        z->color = BLACK;
        T = z;
    }
    return T;
}

RBTree *RB_insert (RBTree *T, NODE *z)
{
    NODE *p = T;
    NODE *next;

    makeRoot(z);
    if( T == NULL) {
        return z; 
    }
    z->color = RED; 
    
    next = p->key > z->key ? p->left : p->right;
    while(next != nil) {
        p = next;
        next = p->key > z->key ? p->left : p->right;
    }
    if(p->key > z->key)
        p->left = z;
    else
        p->right = z;
    z->parent = p;

    return RB_insert_fixup(T, z);
}

RBTree *RB_delete_fixup(RBTree *T, NODE *z)
{

}

RBTree *RB_delete (RBTree *T, NODE *z)
{
    
}

