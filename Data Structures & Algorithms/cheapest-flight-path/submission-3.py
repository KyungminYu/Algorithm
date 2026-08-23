class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        # PASS: BFS
        graph = [[] for _ in range(n + 1)]
        minCost = [int(1e9) for _ in range(n + 1)]

        for s, d, price in flights:
            graph[s].append((d, price))
        que = deque()
        minCost[src] = 0
        que.append([src, minCost[src]])
        stopCount = 0

        while que and stopCount <= k:
            curLen = len(que)
            for idx in range(curLen):
                s, cost = que.popleft()
                for d, price in graph[s]:
                    if cost + price < minCost[d]:
                        minCost[d] = cost + price
                        que.append([d, minCost[d]])
            stopCount += 1

        return minCost[dst] if minCost[dst] != int(1e9) else -1