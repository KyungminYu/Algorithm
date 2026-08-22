# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        # PASS: Slow and Fast Pointer 
        slow = head
        fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        # Utilize [Reverse Linked List]
        second = slow.next
        slow.next = None

        prev = None
        while second:
            tmp = second.next
            second.next = prev
            prev = second
            second = tmp

        # Merge
        first = head
        second = prev
        while second:
            tmp1 = first.next
            tmp2 = second.next
            first.next = second
            second.next = tmp1
            first = tmp1
            second = tmp2

