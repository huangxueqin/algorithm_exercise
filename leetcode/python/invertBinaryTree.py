Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param {TreeNode} root
    # @return {TreeNode}
    def invertTree(self, root):
        if root:
            t = root.left
            root.left = root.right
            root.right = t
            self.invertTree(root.left)
            self.invertTree(root.right)
        return root
