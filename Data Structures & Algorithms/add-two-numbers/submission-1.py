# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        # PASS: Recursive

        def add(l1: Optional[ListNode], l2: Optional[ListNode], carry: int) -> Optional[ListNode]:
            if not l1 and not l2 and carry == 0:
                return None

            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0

            val = val1 + val2 + carry
            carry = val // 10
            val = val % 10

            newNode = ListNode(val)
            newNode.next = add(
                l1.next if l1 else None,
                l2.next if l2 else None,
                carry
            )
            return newNode
        return add(l1, l2, 0)
        