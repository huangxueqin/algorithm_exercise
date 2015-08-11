#include "leetc.h"

using namespace std;

class BSTIterator {
private:
    vector<TreeNode *> tvec;
    TreeNode *next_node;
private:
    void build_path(TreeNode *root) {
        while(root != NULL) {
            tvec.push_back(root);
            root = root->left;
        }
    }
    void update_next() {
        if(tvec.empty()) {
            next_node = NULL;
            return;
        }
        next_node = tvec.back();
        tvec.pop_back();
        if(next_node->right != NULL)
            build_path(next_node->right);
    }
public:
    BSTIterator(TreeNode *root) {
        build_path(root);
        update_next();
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return next_node != NULL;
    }

    /** @return the next smallest number */
    int next() {
        int result = next_node->val;
        update_next();
        return result;
    }
};

int main(void) {
    TreeNode *root = NULL;
    BSTIterator iter(root);
    return 0;
}
