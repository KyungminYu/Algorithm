class Node:
    def __init__(self, key: int, val: int):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.cap = capacity
        self.cache = {}

        self.start = Node(-1, -1)
        self.end = Node(-1, -1)
        self.start.next = self.end
        self.end.prev = self.start

    def insert(self, key: int, val: int):
        newNode = Node(key, val)
        postNode = self.start.next
        newNode.next = postNode
        newNode.prev = self.start
        postNode.prev = newNode
        self.start.next = newNode
        self.cache[key] = newNode

    def remove(self, key: int):
        if key not in self.cache:
            return
        node = self.cache[key]
        preNode = node.prev
        postNode = node.next
        preNode.next = postNode
        postNode.prev = preNode
        del self.cache[key]

    def get(self, key: int) -> int:
        if key in self.cache:
            val = self.cache[key].val
            self.remove(key)
            self.insert(key, val)
            return val
        return -1

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.remove(key)
            self.insert(key, value)
        else:
            self.insert(key, value)
            if len(self.cache) > self.cap:
                self.remove(self.end.prev.key)







        
