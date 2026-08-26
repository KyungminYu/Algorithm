# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        inorderIndices = {}
        for idx, val in enumerate(inorder):
            inorderIndices[val] = idx
        self.preIdx = 0

        def solve(l: int, r: int) -> Optional[TreeNode]:
            if l > r:
                return None
            rootVal = preorder[self.preIdx]
            self.preIdx += 1
            root = TreeNode(rootVal)
            mid = inorderIndices[rootVal]
            root.left = solve(l, mid - 1)
            root.right = solve(mid + 1, r)
            return root
        return solve(0, len(preorder) - 1)