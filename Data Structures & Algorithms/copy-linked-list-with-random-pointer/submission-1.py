"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return None
        cache = {}

        def copyNode(node: 'Optional[Node]') -> 'Optional[Node]':
            if not node:
                return None
            if node in cache:
                return cache[node]
            newNode = Node(node.val)
            cache[node] = newNode
            newNode.next = copyNode(node.next)
            newNode.random = copyNode(node.random)
            return newNode

        return copyNode(head)
        