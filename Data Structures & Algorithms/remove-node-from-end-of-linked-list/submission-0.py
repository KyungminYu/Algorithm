# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        # PASS: Brute Force
        nodes = []
        cur = head
        while cur:
            nodes.append(cur)
            cur = cur.next
        removeIdx = len(nodes) - n
        if removeIdx == 0:
            return head.next
        nodes[removeIdx - 1].next = nodes[removeIdx].next
        return head
        