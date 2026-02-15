```
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        num = 0
        if l1 is not None:
            num += l1.val
        if l2 is not None:
            num += l2.val
        digit = num % 10
        res = ListNode(digit)

        nextL1 = None
        if l1 is not None:
            nextL1 = l1.next
        nextL2 = None
        if l2 is not None:
            nextL2 = l2.next

        carry = num // 10
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
```

In basic calculation logic, we have to compute carry and digit. 
And I will make ListNode from these values.

I compute value num as the sum of the current digits from l1 and l2 if they valid.
From value num, I derive digit and carry.
digit is computed as a num % 10 for the current node's value.
carry is computed as a num // 10 for the carry to the next position.

I create a result node with value digit.
Then I move to the next nodes 
If value carry is zero, I just recurse to the next nodes when at least one list still has nodes.
if carry is not zero, I add this value to the nextL1 or nextL2 that is valid.
It there is no valid node, I make  ListNode with carry and put it to result's next 

The reason why I do not add extra parameter in the addTwoNumbers method.
Time and Space complexity is O(n)