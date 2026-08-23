class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        # PASS: Heap
        graph = [[] for _ in range(n)]

        for s, d, price in flights:
            graph[s].append((d, price))
        
        costs = [[int(1e9)] * (k + 2) for _ in range(n)]
        pq = []
        
        costs[src][0] = 0
        heapq.heappush(pq, (0, src, 0)) # cost, start, stops

        while pq:
            cost, start, stops = heapq.heappop(pq)
            if start == dst:
                return cost
            if stops > k:
                continue
            for dest, price in graph[start]:   
                nxt_cost = cost + price
                nxt_stops = stops + 1
                if nxt_cost < costs[dest][nxt_stops]:
                    costs[dest][nxt_stops] = nxt_cost
                    heapq.heappush(pq, (nxt_cost, dest, nxt_stops))
        return -1