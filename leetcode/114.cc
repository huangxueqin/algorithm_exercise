#include "leetc.h"

using namespace std;

class Solution {
    private:
        TreeNode *flatten_sub(TreeNode *root) {
            TreeNode *right_child = root->right;
            TreeNode *left_child = root->left;
            root->left = NULL;
            root->right = NULL;
            if(right_child == NULL && left_child == NULL)
                return root;
            else if(left_child == NULL) {
                root->right = right_child;
                return flatten_sub(right_child);
            }
            else if(right_child == NULL) {
                root->right = left_child;
                return flatten_sub(left_child);
            }
            else {
                root->right = left_child;
                flatten_sub(left_child)->right = right_child;
                return flatten_sub(right_child);
            }
        }
    public:
        void flatten(TreeNode *root) {
            if(root == NULL) return;
            flatten_sub(root);
        }
    };

void delete_tree(TreeNode *root) {
    if(root->right != NULL)
        delete_tree(root->right);
    if(root->left != NULL)
        delete_tree(root->left);
    delete(root);
}

void print_flattened_tree(TreeNode *root) {
    if(root != NULL) {
        printf("%d ", root->val);
        print_flattened_tree(root->right);
    }
}

int main(void) {
    TreeNode *t1 = new TreeNode(1);
    t1->left = new TreeNode(2);
    t1->right = new TreeNode(5);
    t1->left->left = new TreeNode(3);
    t1->left->right = new TreeNode(4);
    t1->right->right = new TreeNode(6);

    TreeNode *t2 = new TreeNode(1);
    t2->right = new TreeNode(2);
    Solution s;
    s.flatten(t2);
    print_flattened_tree(t2);
    printf("\n");
    delete_tree(t1);
    delete_tree(t2);
    return 0;
}
