#include "leetc.h"

using namespace std;

class Solution {
    public:
        vector<vector<int>> pathSum(TreeNode *root, int sum) {
            vector<vector<int>> result;
            vector<int> path;
            if(root == NULL)
                return result;
            get_path(root, sum, 0, result, path);
            return result;
        }
    private:
        void get_path(const TreeNode *root, const int sum, int current, 
                vector<vector<int>> &result, vector<int> &path) {
            if(root == NULL) return;
            path.push_back(root->val);
            current += root->val;
            if(root->left == NULL && root->right == NULL) {
                if(current == sum)
                    result.push_back(path);
            }
            else if(root->left == NULL) {
                get_path(root->right, sum, current, result, path);
            }
            else if(root->right == NULL) {
                get_path(root->left, sum, current, result, path);
            }
            else {
                get_path(root->left, sum, current, result, path);
                get_path(root->right, sum, current, result, path);
            }
            path.pop_back();
        }
};
