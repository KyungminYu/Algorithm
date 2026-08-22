# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        # PASS: Brute Force(Do not use nodes list)
        cur = head
        nodeCount = 0
        while cur:
            nodeCount += 1
            cur = cur.next
        removeIdx = nodeCount - n
        if removeIdx == 0:
            return head.next
        
        cur = head
        for i in range(nodeCount - 1):
            if i + 1 == removeIdx:
                cur.next = cur.next.next
                break
            cur = cur.next
        return head
        