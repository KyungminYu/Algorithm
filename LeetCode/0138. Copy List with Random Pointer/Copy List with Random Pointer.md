```
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
        cache = {}
        
        def deep_copy(node: 'Optional[Node]') -> 'Optional[Node]':
            if not node:
                return None
            if node in cache:
                return cache[node]
            new_node = Node(node.val)
            cache[node] = new_node
            new_node.next = deep_copy(node.next)
            new_node.random = deep_copy(node.random)
            return new_node

        return deep_copy(head)
```

To solve it, I will use linked list traversal with caching.
I will create node if node does not exist in cache. 
If not, I will return cached nodes and do not traverse cached node's children anymore.
In this case, node's val can be duplicated, so we have to use key as node itself
Its time complexity is O(n) and space complexity is O(n) also.
