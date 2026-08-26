# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:

        def solve(node: Optional[TreeNode], nodes: List):
            if not node:
                return
            solve(node.left, nodes)
            nodes.append(node.val)
            solve(node.right, nodes)
        nodes = []
        solve(root, nodes)
        return nodes[k - 1]