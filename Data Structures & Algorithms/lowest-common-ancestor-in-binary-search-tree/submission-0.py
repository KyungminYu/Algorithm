# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        depth = {}
        def traverse(node: TreeNode, d: int):
            if not node:
                return
            depth[node.val] = d
            traverse(node.left, d + 1)
            traverse(node.right, d + 1)

        traverse(root, 0)

        parents = {}
        def setupParents(parent: TreeNode, node: TreeNode):
            if not node:
                return
            if not parent:
                parents[node] = None
            else:
                parents[node] = parent

            setupParents(node, node.left)
            setupParents(node, node.right)

        setupParents(None, root)

        while depth[p.val] != depth[q.val]:
            if depth[p.val] > depth[q.val]:
                p = parents[p]
            else:
                q = parents[q]
        
        while p != q:
            p = parents[p]
            q = parents[q]
        return p






