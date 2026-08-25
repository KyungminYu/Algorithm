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

            lHeight = 0
            if node.left:
                lHeight = 1 + solve(node.left)

            rHeight = 0
            if node.right:
                rHeight = 1 + solve(node.right)

            self.res = max(self.res, lHeight + rHeight)
            return max(lHeight, rHeight)
        solve(root)
        return self.res