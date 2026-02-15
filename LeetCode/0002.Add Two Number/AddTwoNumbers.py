class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        num = 0
        if l1 is not None:
            num += l1.val
        if l2 is not None:
            num += l2.val
        carry = num // 10
        digit = num % 10
        res = ListNode(digit)

        nextL1 = None
        if l1 is not None:
            nextL1 = l1.next
        nextL2 = None
        if l2 is not None:
            nextL2 = l2.next

        if carry == 0:
            if nextL1 is not None or nextL2 is not None:
                res.next = self.addTwoNumbers(nextL1, nextL2)
        else:
            if nextL1 is not None:
                nextL1.val += carry
                res.next = self.addTwoNumbers(nextL1, nextL2)
            elif nextL2 is not None:
                nextL2.val += carry
                res.next = self.addTwoNumbers(nextL1, nextL2)
            else:
                res.next = ListNode(carry)
        return res