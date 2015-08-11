#include "leetc.h"

using namespace std;

class Solution {
    public:
        bool isValidBST(TreeNode *root) {
            if(root == NULL) return true;
            if(root->left != NULL) {
                if(!isValidBST(root->left)) return false;
            }
            if(root->right != NULL) {
                if(!isValidBST(root->right)) return false;
            }
            if(root->left != NULL) {
                if(root->val <= max_val(root->left)) return false;
            }
            if(root->right != NULL) {
                if(root->val >= min_val(root->right)) return false;
            }
            return true;
        }
    private:
        int max_val(TreeNode *root) {
            return root->right == NULL ? root->val : max_val(root->right);
        }
        int min_val(TreeNode *root) {
            return root->left == NULL ? root->val : min_val(root->left);
        }
};

Solution sol;
