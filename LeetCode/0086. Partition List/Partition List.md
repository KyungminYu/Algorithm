```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def partition(self, head: ListNode | None, x: int) -> ListNode | None:
        lower_head = ListNode()
        greater_head = ListNode()
        lower = lower_head
        greater = greater_head
        while head:
            if head.val < x:
                lower.next = ListNode(head.val)
                lower = lower.next
            else:
                greater.next = ListNode(head.val)
                greater = greater.next
            head = head.next
        lower.next = greater_head.next
        return lower_head.next
```

I will use linked list traversal, 
First, I will define lower_head, greater_head for partitioning nodes with keeping their order.
Second, until head is not null, I will traverse all nodes and connect them.
Third, I will connect end of lower and start of greater.
Its time complexity is O(n), and space complexity is O(n)