```
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        graph = defaultdict(list)
        def make_graph(node: TreeNode):
            if not node:
                return
            if node.left:
                graph[node.val].append(node.left.val)
                graph[node.left.val].append(node.val)
                make_graph(node.left)
            if node.right:
                graph[node.val].append(node.right.val)
                graph[node.right.val].append(node.val)
                make_graph(node.right)
        make_graph(root)

        res = []
        visited = set()
        def traverse(node: int, depth: int):
            if depth == k:
                res.append(node)
                return
            visited.add(node)
            for nxt in graph[node]:
                if nxt in visited:
                    continue
                traverse(nxt, depth + 1)

        traverse(target.val, 0)
        return res
```

I use binary search and graph traversal to solve it
First, I generate graph, by traverse all binary tree nodes and connecting parent and children.
Second, from target value, I start traversal until depth k, and collect k th nodes
Its time complexity is O(n, n is # of nodes) and space complexity is O(n)
