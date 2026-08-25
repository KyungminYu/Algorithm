# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def goodNodes(self, root: TreeNode) -> int:

        def solve(node: TreeNode, curMax: int) -> int:
            if not node:
                return 0

            res = 1 if node.val >= curMax else 0
            curMax = max(curMax, node.val)
            res += (solve(node.left, curMax) + solve(node.right, curMax))
            return res
            
        return solve(root, -101)