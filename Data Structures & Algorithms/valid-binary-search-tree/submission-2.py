# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        vals = []

        def traverse(node: Optional[TreeNode]):
            if not node:
                return
            traverse(node.left)
            vals.append(node.val)
            traverse(node.right)
        
        traverse(root)
        for i in range(len(vals) - 1):
            if vals[i] >= vals[i + 1]:
                return False
        return True