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
