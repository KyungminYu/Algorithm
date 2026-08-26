# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        self.res = -30000000

        def solve(node: Optional[TreeNode]) -> int:
            if not node:
                return 0
            val = node.val
            lVal = max(0, solve(node.left))
            rVal = max(0, solve(node.right))
            self.res = max(self.res, node.val + lVal + rVal)
            return node.val + max(lVal, rVal)
        solve(root)
        return self.res
        