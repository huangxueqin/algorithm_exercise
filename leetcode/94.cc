#include "leetc.h"
#include <stack>

using namespace std;

class Solution {
    public:
        vector<int> inorderTraversal(TreeNode *root) {
            vector<int> result;
            literalTraversal(root, result);
            return result;
        }
    private:
        void recursiveTraversal(TreeNode *root, vector<int> &result) {
            if(root != NULL) {
                recursiveTraversal(root->left, result);
                result.push_back(root->val);
                recursiveTraversal(root->right, result);
            }
        }
        void literalTraversal(TreeNode *root, vector<int> &result) {
            stack<TreeNode *> tn_stack;
            fill_stack(root, tn_stack);
            while(!tn_stack.empty()) {
                TreeNode *node = tn_stack.top(); tn_stack.pop();
                result.push_back(node->val);
                if(node->right != NULL)
                    fill_stack(node->right, tn_stack);
            }
        }
        void fill_stack(TreeNode *root, stack<TreeNode *> &tn_stack) {
            while(root != NULL) {
                tn_stack.push(root);
                root = root->left;
            }
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    return 0;
}
