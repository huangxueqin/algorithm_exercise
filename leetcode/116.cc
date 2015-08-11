#include "leetc.h"

using namespace std;

class Solution {
    public:
        void connect(TreeLinkNode *root) {
            if(root == NULL) return;
            connect_child(root);
        }
    private:
        void connect_child(TreeLinkNode *parent) {
            if(parent->left == NULL) return;
            parent->left->next = parent->right;
            parent->right->next = parent->next == NULL ? NULL : parent->next->left;
            connect_child(parent->left);
            connect_child(parent->right);
        }
};
