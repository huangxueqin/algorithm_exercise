#ifndef _BS_TREE_H_
#define _BS_TREE_H_

typedef int E;

struct bs_tree {
    E data;
    int key;

    struct bs_tree *left, *right, *parent;
};

typedef struct bs_tree NODE;
typedef struct bs_tree ROOT;

#endif
