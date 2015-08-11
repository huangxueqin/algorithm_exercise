#include "leetc.h"

class Solution {
    public:
        int kthSmallest(TreeNode *root, int k) {
            int result = 0;
            traverse(root, k, result);
            return k;
        }
    private:
        void traverse(TreeNode *root, int &k, int &result) {
            if(k < 1) return;
            if(root == NULL) return;
            traverse(root->left, k, result);
            if(k == 1) {
                result = root->val;
            }
            k -= 1;
            traverse(root->right, k, result);
        }
};
