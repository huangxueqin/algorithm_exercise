from collections import deque
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param {TreeNode} root
    # @return {integer[][]}
    def levelOrderBottom(self, root):
        result = []
        if root:
            level = []
            queue = deque([root, None])
            while queue:
                node = queue.popleft()
                if not node:
                    if level:
                        result.append(level)
                        level = []
                        if queue:
                            queue.append(None)
                else:
                    level.append(node.val)
                    if node.left:
                        queue.append(node.left)
                    if node.right:
                        queue.append(node.right)
        if result:
            result.reverse()
        return result
