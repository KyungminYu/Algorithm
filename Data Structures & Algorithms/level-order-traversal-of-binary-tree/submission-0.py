# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        res = []

        def solve(node: Optional[TreeNode], d: int):
            if not node:
                return
            if len(res) <= d:
                res.append([])
            res[d].append(node.val)
            solve(node.left, d + 1)
            solve(node.right, d + 1)

        solve(root, 0)
        return res