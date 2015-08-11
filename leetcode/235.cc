#include "leetc.h"

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        int l = p->val < q->val ? p->val : q->val;
        int r = p->val < q->val ? q->val : p->val;
        TreeNode *result = root;
        while(true) {
            int t = result->val;
            if(t > r) {
                result = result->left;
            }
            else if(t < l) {
                result = result->right;
            }
            else 
                break;
        }
        return result;
    }
};
