```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        if not head or not head.next:
            return

        slow, fast = head, head
        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next
        
        prev, curr = None, slow.next
        slow.next = None
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt

        first, second = head, prev
        while second:
            tmp1, tmp2 = first.next, second.next
            first.next = second
            second.next = tmp1
            first, second = tmp1, tmp2
```

To solve it, I will just traverse all nodes.
First, I will find mid point of the linked list by using fast, slow pointer
Second, I will reverse last half of linked list 
Third, I will append front node and last node.
Its time complexity is O(n) and space complexity is O(1)


```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reorderList(self, head: ListNode | None) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
       dummy = head
        nodes = []
        while dummy:
            nodes.append(dummy)
            dummy = dummy.next
        for node in nodes:
            node.next = None
        l = 1
        r = len(nodes) - 1
        dummy = head
        while l <= r:
            dummy.next = nodes[r]
            dummy = dummy.next
            r -= 1
            if l <= r:
                dummy.next = nodes[l]
                dummy = dummy.next
                l += 1
```

To solve it, I will just collect nodes and release connection
And then, I will reorder them as given order
Its time complexity is O(n) and space complexity is O(n)