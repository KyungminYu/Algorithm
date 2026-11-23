```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def reverseBetween(self, head: ListNode | None, left: int, right: int) -> ListNode | None:  

        if not head or left == right:
            return head

        dummy = ListNode(0, head)
        prev = dummy

        for _ in range(left - 1):
            prev = prev.next

        curr = prev.next
        for _ in range(right - left):
            nxt = curr.next
            curr.next = nxt.next
            nxt.next = prev.next
            prev.next = nxt

        return dummy.next
```

I will use in-palace head insertion approach.
First, I create a dummy node pointing to head.
so I don't have to handle the edge case where left is 1 and the head itself changes.
Next, I move prev to the node right before the reversal section, 
and set curr to the first node of the sublist. 
The key here is that neither prev nor curr moves during the reversal—they act as fixed anchors.
Then, I iterate right - left times. 
In each step, I extract the node right after curr (nxt) and insert it right after prev—at the front of the sublist. 
As subsequent nodes get pulled to the front, curr naturally shifts to the end of the reversed section.
Since we traverse the list only once without extra memory, 
it runs in $O(N)$ time and $O(1)$ space.


```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseBetween(self, head: ListNode | None, left: int, right: int) -> ListNode | None:  

        nodes = []
        dummy = head
        while dummy:
            nodes.append(dummy)
            dummy = dummy.next
        for node in nodes:
            node.next = None
        new_head = ListNode()
        dummy = new_head
        for i in range(left - 1):
            dummy.next = nodes[i]
            dummy = dummy.next

        for i in range(right - 1, left - 2, -1):
            dummy.next = nodes[i]
            dummy = dummy.next
        
        for i in range(right, len(nodes)):
            dummy.next = nodes[i]
            dummy = dummy.next
        return new_head.next
```

I will use array to solve it.
First, I will collect all nodes and release each node's next
Second, connect it as a given order
Its time complexity is O(n) and space complexity is O(n)
