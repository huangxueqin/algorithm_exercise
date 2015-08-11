#ifndef _CLEETC_H_
#define _CLEETC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

extern inline struct ListNode *create_list_node
(
 int val,
 struct ListNode *next) {
    struct ListNode *p = (struct ListNode *) malloc(sizeof(struct ListNode));
    p->val = val;
    p->next = next;
    return p;
}

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

extern inline struct TreeNode *create_tree_node
(
 int val,
 struct TreeNode *left,
 struct TreeNode *right) {
    struct TreeNode *p = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    p->val = val;
    p->left = left;
    p->right = right;
    return p;
}

extern inline int clamp(int a, int b, int c) {
    if(c < a) return a;
    if(c > b) return b;
    return c;
}

#endif
