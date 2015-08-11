#include "leetc.h"

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        vector<int> pathp = getPath(root, p);
        vector<int> pathq = getPath(root, q);
        TreeNode *ancestor = root;
        for(int i = 0; i < pathp.size() && i < pathq.size() && pathp[i] == pathq[i]; i++) {
            if(pathp[i]) {
                ancestor = ancestor->right;
            }
            else {
                ancestor = ancestor->left;
            }
        }
        return ancestor;
    }
private:
    vector<int> getPath(TreeNode *root, TreeNode *p) {
        vector<int> path;
        if(root != p) {
            if(root->left) {
                path.push_back(0);
                if(!search(root->left, p, path)) {
                    path.pop_back();
                }
            }
            if(root->right) {
                path.push_back(1);
                if(!search(root->right, p, path)) {
                    path.pop_back();
                }
            }
        }
        else {
            path.push_back(-1);
        }
        return path;
    }
    bool search(TreeNode *root, TreeNode *p, vector<int> &path) {
        if(root == p) return true;
        else {
            if(root->left) {
                path.push_back(0);
                if(search(root->left, p, path)) {
                    return true;
                }
                else {
                    path.pop_back();
                }
            }
            if(root->right) {
                path.push_back(1);
                if(search(root->right, p, path)) {
                    return true;
                }
                else {
                    path.pop_back();
                }
            }
        }
        return false;
    }
};
