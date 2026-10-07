# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        self.res = 0
        def solve(node: Optional[TreeNode]) -> int:
            if not node:
                return 0

            lMax = solve(node.left)
            rMax = solve(node.right)

            self.res = max(self.res, lMax + rMax)

            return max(lMax, rMax) + 1
        solve(root)
        return self.res