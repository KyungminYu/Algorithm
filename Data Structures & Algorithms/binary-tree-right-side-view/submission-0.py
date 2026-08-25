# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        res = []

        def solve(node: Optional[TreeNode], depth: int):
            if not node:
                return

            if len(res) <= depth:
                res.append(node.val)

            solve(node.right, depth + 1)
            solve(node.left, depth + 1)

        solve(root, 0)
        return res