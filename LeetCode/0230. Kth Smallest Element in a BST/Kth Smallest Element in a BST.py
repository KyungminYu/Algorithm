# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def kthSmallest(self, root: TreeNode | None, k: int) -> int:
        # I will use BST's inorder traversal approach and pick k the element directly.
        # Its time complexity is O(n) and space complexity is O(n)
        inorders = []

        def traverse(node: TreeNode | None):
            if not node:
                return
            traverse(node.left)
            inorders.append(node.val)
            traverse(node.right)

        traverse(root)
        return inorders[k - 1]