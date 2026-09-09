class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        graph = defaultdict(list)
        for t in times:
            graph[t[0]].append(t[1:])
        pq = []
        heapq.heappush(pq, (0, k))
        visited = set()

        res = 0

        while pq:
            time, node = heapq.heappop(pq)
            if node in visited:
                continue
            visited.add(node)
            res = time
            for nxt_node, nxt_time in graph[node]:
                if nxt_node not in visited:
                    heapq.heappush(pq, (time + nxt_time, nxt_node))

        return -1 if len(visited) < n else res