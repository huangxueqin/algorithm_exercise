#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define BLACK 1
#define RED 0

struct rbtree {
    int color;
    int key;
    struct rbtree *left, *right, *p;
};

typedef struct rbtree RBTree;
typedef struct rbtree NODE;

extern NODE *nil;
#endif
