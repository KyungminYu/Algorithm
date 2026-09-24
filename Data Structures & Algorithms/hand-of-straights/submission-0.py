class Solution:
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:
        if len(hand) % groupSize != 0:
            return False
        pq = []
        count = [0] * 1001
        for h in hand:
            count[h] += 1
            heapq.heappush(pq, h)
        
        group = []
        while len(pq) > 0:
            cur = heapq.heappop(pq)
            if count[cur] == 0:
                continue
            count[cur] -= 1
            group = [cur]
            cur += 1
            for i in range(groupSize - 1):
                if count[cur] == 0:
                    return False
                count[cur] -= 1
                group.append(cur)
                cur += 1
        return len(group) == groupSize