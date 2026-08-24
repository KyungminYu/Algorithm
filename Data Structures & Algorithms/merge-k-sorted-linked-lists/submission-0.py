# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class NodeWrapper:
    def __init__(self, node: Optional[ListNode]):
        self.node = node
    
    def __lt__(self, other: NodeWrapper):
        return self.node.val < other.node.val

class Solution:    
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        head = ListNode()
        cur = head
        pq = []

        for node in lists:
            if node:
                heapq.heappush(pq, NodeWrapper(node))

        while pq:
            nodeWrapper = heapq.heappop(pq)
            cur.next = nodeWrapper.node
            cur = cur.next
            nodeWrapper.node = nodeWrapper.node.next
            if nodeWrapper.node:
                heapq.heappush(pq, nodeWrapper)

        return head.next
        