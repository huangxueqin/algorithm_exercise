#ifndef _LEETC_H_
#define _LEETC_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using std::vector;
using std::string;
using std::printf;
using std::scanf;
using std::cout;
using std::cin;
using std::endl;

typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ~ListNode() {
        if(this->next != NULL) 
            delete this->next;
    }  
    static void print_list(ListNode *head) {
        while(head != NULL) {
            std::printf("%d ", head->val);
            head = head->next;
        }
        printf("\n");
    }
} ListNode;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    static void destroy_tree(TreeNode *root) {
        if(root == NULL) return;
        std::queue<TreeNode *> tn_queue;
        tn_queue.push(root);
        while(!tn_queue.empty()) {
            TreeNode *tn = tn_queue.front();
            tn_queue.pop();
            if(tn->left != NULL) tn_queue.push(tn->left);
            if(tn->right != NULL) tn_queue.push(tn->right);
            delete tn;
        }
    }
} TreeNode;

typedef struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
}TreeLinkNode;

typedef struct UndirectedGraphNode {
    int label;
    std::vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
} UndirectedGraphNode;


/* common use functions */
/* print a table */
template <typename T>
void print_table(const std::vector<std::vector<T>> &table) {
    for(int i=0;i<table.size();i++) {
        for(int j=0;j<table[i].size();j++)
            std::cout << table[i][j] << " ";
        std::cout << std::endl;
    }
}

/* print a vector */
template <typename T>
void print_vector(std::vector<T> &vec) {
    typename std::vector<T>::iterator iter = vec.begin();
    while(iter != vec.end()) {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << std::endl;
}

/* deserialize a tree out of an int array */
TreeNode *deserialize_tree(int a[], size_t n) {
    TreeNode *root = NULL;
    if(n > 0) {
        if(a[0] != '#') {
            root = new TreeNode(a[0]);
            std::queue<TreeNode *> tn_queue;
            tn_queue.push(root);
            size_t i = 1;
            while(i < n) {
                if(tn_queue.empty()) break;
                TreeNode *t_node = tn_queue.front();
                tn_queue.pop();
                if(a[i] != '#') {
                    t_node->left = new TreeNode(a[i]);
                    tn_queue.push(t_node->left);
                }
                i++;
                if(i < n) {
                    if(a[i] != '#') {
                        t_node->right = new TreeNode(a[i]);
                        tn_queue.push(t_node->right);
                    }
                    i++;
                }
            }
        }
    }
    return root;
}

/* serialize a tree */
std::vector<int> serialize_tree(TreeNode *root) {
    std::vector<int> result;
    if(root != NULL) {
        std::queue<TreeNode *> tn_queue;
        TreeNode *nil = new TreeNode('#');
        tn_queue.push(root);
        while(!tn_queue.empty()) {
            TreeNode *t_node = tn_queue.front();
            tn_queue.pop();
            result.push_back(t_node->val);
            if(t_node->val != '#') {
                TreeNode *left = t_node->left == NULL ?
                    nil : t_node->left;
                TreeNode *right = t_node->right == NULL ?
                    nil : t_node->right;
                tn_queue.push(left);
                tn_queue.push(right);
            }
        }
        delete nil;
        while(!result.empty()) {
            if(result.back() == '#') result.pop_back();
            else break;
        }
    }
    return result;
}

/* deserialize a list */
ListNode *deserialize_list(int a[], size_t n) {
    ListNode *head = n > 0 ? new ListNode(a[0]) : NULL;
    ListNode *node = head;
    for(size_t i = 1; i < n; i++) {
        node->next = new ListNode(a[i]);
        node = node->next;
    }
    node->next = NULL;
    return head;
}

/* serialize a list */
std::vector<int> serialize_list(ListNode *head) {
    std::vector<int> result;
    while(head != NULL) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

#endif
