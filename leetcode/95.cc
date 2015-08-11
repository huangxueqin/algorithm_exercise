#include "leetc.h"

using namespace std;

class Solution {
    public:
        vector<TreeNode *> generateTrees(int n) {
            return generateTrees(1, n);
        }
    private:
        vector<TreeNode *> generateTrees(int i, int j) {
            vector<TreeNode *> result;
            if(i > j) {
                result.push_back(NULL);
                return result;
            }
            for(int k = i; k <= j; k++)
                create_tree(k, generateTrees(i, k-1), generateTrees(k+1, j), result);
            return result;
        }
        void create_tree(int k, vector<TreeNode *> left, vector<TreeNode *> right,
                vector<TreeNode *> &result) {
            for(auto lit = left.begin(); lit != left.end(); lit++) 
                for(auto rit = right.begin(); rit != right.end(); rit++) {
                    TreeNode *root = new TreeNode(k);
                    root->left = *lit;
                    root->right = *rit;
                    result.push_back(root);
                }
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    return 0;
}
