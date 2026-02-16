```
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        if subRoot is None:
            return True
        elif root is None:
            return False

        if self.isSameTree(root, subRoot):
            return True

        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)

    def isSameTree(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        if root1 is None and root2 is None:
            return True
        elif root1 is None or root2 is None:
            return False
        elif root1.val != root2.val:
            return False
        return self.isSameTree(root1.left, root2.left) and self.isSameTree(root1.right, root2.right)
```

### GPT revised
I solved this using DFS on the main tree.

I wrote a helper isSameTree(a, b) that checks whether two trees are identical by comparing values 
and recursively matching left and right children; 

it returns true only if both structures and values match.

In isSubtree, I traverse every node in root. 
At each node, I first run isSameTree(root, subRoot). 
If it matches, I return true immediately. 
Otherwise, I continue the search on root.left and root.right.

Time complexity is O(N * M) in the worst case, 
because for each node in root I might compare up to all nodes in subRoot. 
Space complexity is O(H + h) for recursion depth.

### My solution

I used Tree and DFS approach to solve this problem.
First, I define a isSameTree method that uses recursive call with traverse two tree with same direction.
Second. I use a isSameTree method in the isSubTree method to check current root is same with subRoot.
Otherwise, I check both way left and right.