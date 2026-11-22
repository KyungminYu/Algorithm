# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def deleteNode(self, root: TreeNode | None, key: int) -> TreeNode | None:
        # I will use BST traversal approach first.
        # First, I will find key's node reference.
        # Second. I will replace it with one of its children's leaf node's value and delete leaf node directly not to make duplicated nodes.

        def get_left_most_leaf(node: TreeNode | None) -> TreeNode | None:
            if not node:
                return None
            elif not node.left:
                return node
            return get_left_most_leaf(node.left)

        if not root:
            return None
        elif key < root.val:
            root.left = self.deleteNode(root.left, key)
        elif root.val < key:
            root.right = self.deleteNode(root.right, key)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            else:
                l_most_leaf = get_left_most_leaf(root.right)                
                root.val = l_most_leaf.val
                root.right = self.deleteNode(root.right, l_most_leaf.val)
        return root