```
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: TreeNode | None) -> int:
        if not root:
            return 0
        return max(self.maxDepth(root.left), self.maxDepth(root.right)) + 1
        
```
I use binary search to solve it.
First, if root is none, then I will return 0 because there is no node
Second, I return left and right node's maxDepth recursively and then add 1 as a current root node's depth
Its time complexity is O(n, n is # of nodes), and space complexity is O(1)