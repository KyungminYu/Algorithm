"""
# Definition for a Node.
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []
"""

class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        cache = {}

        def clone(node: Optional['Node']) -> Optional['Node']:
            if not node:
                return None
            if node.val in cache:
                return cache[node.val]
            newNode = Node(node.val)
            cache[node.val] = newNode
            for neighbor in node.neighbors:
                newNode.neighbors.append(clone(neighbor))
            return newNode
        
        return clone(node)