# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isValidBST(self, root: TreeNode | None) -> bool:
        # I use definition of BST.
        # Basically, BST's all nodes can be shown as ascending order if I re-write it as a inorder approach.
        # So I will make inorder traverse and then check it is ascending.
        # Its time complexity is O(n) and space complexity is O(n)
        inorders = []
        def traverse(node: TreeNode | None) -> bool:
            if not node:
                return True
            if not traverse(node.left):
                return False
            if inorders and node.val <= inorders[-1]:
                return False
            inorders.append(node.val)
            if not traverse(node.right):
                return False
            return True
        return traverse(root)