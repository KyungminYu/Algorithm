# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def widthOfBinaryTree(self, root: TreeNode | None) -> int:
        # I use binary search and caching to solve it.
        # Basically, I traverses all binary tree element with caching first position for each depth. To cache it, I traverse left node first.
        # Also, in the every traverse, I calculate witdh for each depth
        # Its time complexity is O(n, n is # of nodes), and space complexity is O(log n)
        self.res = 0
        firstPos = {}

        def solve(node: TreeNode | None, depth: int, pos: int) -> int:
            if not node:
                return

            if depth not in firstPos:
                firstPos[depth] = pos

            self.res = max(self.res, pos - firstPos[depth] + 1)

            solve(node.left, depth + 1, pos * 2)
            solve(node.right, depth + 1, pos * 2 + 1)

        solve(root, 0, 0)
        return self.res