```
class Solution:
    def reorganizeString(self, s: str) -> str:
        counts = Counter(s)
        pq = []
        for ch in counts:
            heapq.heappush(pq, [-counts[ch], ch])
        
        res = []
        while pq:
            temp = heapq.heappop(pq) if len(res) > 0 and res[-1] == pq[0][1] else None
            if not pq:
                return ""
            
            val = heapq.heappop(pq)
            ch = val[1]
            count = -val[0] - 1

            res.append(ch)
            if count > 0:
                heapq.heappush(pq, [-count, ch])
            if temp:
                heapq.heappush(pq, temp)
        return "".join(res)

```

I use max heap and greedy approach to solve this problem.
First, I count all character's frequency.
Second, I put counts value to the max heap with its count and key
Third, I compare last appended value and first max heap value's key and if they are same, then I pop the first max heap value to temp variable and ignore it at the current loop.
if max heap is empty, then it means there is no alternative char for temp's key. So I return ""
Forth, I pop the first max heap value and append character to the res array. Also, there is remained count I push this character again to the max heap.
I repeat Third to Forth until pq is not empty.

This logic has O(n log n) time complexity and O(n) space complexity.