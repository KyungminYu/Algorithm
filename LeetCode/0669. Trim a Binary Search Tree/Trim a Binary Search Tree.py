# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def trimBST(self, root: TreeNode | None, low: int, high: int) -> TreeNode | None:
        # I will use definition of BST.
        # In this case, I think I have to cut invalid nodes directly and connect invalid node's children if they are valid.
        # if root value is lower than low value, then I drop current root and return its trimmed right child, and drop left node also
        # if root value is higher than high value, then I also drop current root and return itss trimmed left child, and drop right node
        # if root value is inside of the range, then I connect trimmed left, and right node to the current node.
        # Its time complexity is O(n) and space complexity is also O(n)
        if not root:
            return None
        elif root.val < low:
            return self.trimBST(root.right, low, high)
        elif high < root.val:
            return self.trimBST(root.left, low, high)
        root.left = self.trimBST(root.left, low, high)
        root.right = self.trimBST(root.right, low, high)
        return root