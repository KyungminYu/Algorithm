# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        # I use binary search to solve it.
        # Basically, I calculate depth of each node in the solve method.
        # During this process, I update diameter of Binary Tree by calculate sum of left_depth and right_depth
        # Its time complexity is O(n, n is # of node), and space complexity is O(1)

        self.res = 0

        def solve(node: Optional[TreeNode]) -> int:
            if not node:
                return 0
            l_depth = solve(node.left)
            r_depth = solve(node.right)
            self.res = max(self.res, l_depth + r_depth)
            return max(l_depth, r_depth) + 1

        solve(root)
        return self.res
