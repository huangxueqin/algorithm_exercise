#include "leetc.h"
#include <stack>

using namespace std;

class Solution {
    public:
        vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
            vector<vector<int>> result;
            solution(result, root);
            return result;
        }
    private:
        void solution(vector<vector<int>> &result, TreeNode *root) {
            if(root != NULL) {
                vector<int> ivec;
                stack<TreeNode *> left_stack;
                stack<TreeNode *> right_stack;
                left_stack.push(root);
                while(!left_stack.empty() || !right_stack.empty()) {
                    if(!left_stack.empty()) {
                        foo(result, left_stack, right_stack, false);
                    }
                    else {
                        foo(result, right_stack, left_stack, true);
                    }
                }
            }
        }

        void foo(vector<vector<int>> &result, 
                stack<TreeNode *> &tq1, stack<TreeNode *> &tq2, bool l2r) {
            vector<int> ivec;
            while(!tq1.empty()) {
                TreeNode *tn = tq1.top();
                ivec.push_back(tn->val);
                if(!l2r) {
                    if(tn->left != NULL) tq2.push(tn->left);
                    if(tn->right != NULL) tq2.push(tn->right);
                }
                else {
                    if(tn->right != NULL) tq2.push(tn->right);
                    if(tn->left != NULL) tq2.push(tn->left);
                }
                tq1.pop();
            }
            result.push_back(ivec);
        }
};

Solution sol;

int main(void) {
    int a[] = {3,9,20,'#','#',15,7};
    int b[] = {1, 3, 2};
    int c[] = {1,2,3,4,'#','#',5};
    TreeNode *root = deserialize_tree(c, 7);
    vector<int> arr = serialize_tree(root);
    print_vector(arr);
    vector<vector<int>> result = sol.zigzagLevelOrder(root);
    print_table(result);
    TreeNode::destroy_tree(root);
    return 0;
}
