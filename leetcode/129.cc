#include "leetc.h"

using namespace std;

class Solution {
    public:
        int sumNumbers(TreeNode *root) {
            return sumNumbers(root, 0);    
        }
    private:
        int sumNumbers(TreeNode *root, int sum) {
            if(root == NULL)
                return sum;
            int result = sum * 10 + root->val;
            if(root->left != NULL && root->right == NULL)
                result = sumNumbers(root->left, result);
            else if(root->right != NULL && root->left == NULL)
                result = sumNumbers(root->right, result);
            else if(root->left != NULL && root->right != NULL)
                result = sumNumbers(root->left, sum * 10 + root->val) + 
                    sumNumbers(root->right, sum * 10 + root->val);
            return result;
        }
};


/* this method is better */
class Solution2 {
    public:
        int sumNumbers(TreeNode *root) {
            vector<vector<int>> ivec;
            vector<int> tmp;
            dfs(ivec, tmp, root);
            return compute_sum(ivec);
        }
    private:
        void dfs(vector<vector<int>> &ivec, vector<int> &tmp, TreeNode *root) {
            if(root == NULL)
                return;
            tmp.push_back(root->val);
            if(root->right == NULL && root->left == NULL) {
                ivec.push_back(tmp);
            }
            else if(root->right != NULL) {
                dfs(ivec, tmp, root->right);
                tmp.pop_back();
            }
            else {
                dfs(ivec, tmp, root->left);
                tmp.pop_back();
            }
        }

        int compute_sum(vector<vector<int>> ivec) {
            int sum = 0;
            vector<vector<int>>::iterator iter = ivec.begin();
            while(iter != ivec.end()) {
                int _sum = 0; 
                vector<int>::iterator inneriter = iter->begin();
                while(inneriter != iter->end()) {
                    _sum = _sum * 10 + *inneriter;
                    inneriter++;
                }
                sum += _sum;
                iter++;
            }
            return sum;
        }
};
