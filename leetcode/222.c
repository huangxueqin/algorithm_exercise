#include "cleetc.h"

int countNodes(struct TreeNode *root, int lc, int rc) {
    if(root == NULL) {
        return 0;
    }
    if(lc < 0) {
        lc = 0;
        struct TreeNode *l = root;
        while(l->left) {
            lc++;
            l = l->left;
        }
    }
    if(rc < 0) {
        rc = 0;
        struct TreeNode *r = root;
        while(r->right) {
            rc++;
            r = r->right;
        }
    }
    if(lc == rc) {
        return (1 << (lc+1)) - 1;
    }
    else {
        return 1 + countNodes(root->left, lc-1, -1) + countNodes(root->right, -1, rc-1);
    }
}

int countNodes(struct TreeNode *root) {
    if(root == 0) return 0;
    return countNodes(root, -1, -1);
}
