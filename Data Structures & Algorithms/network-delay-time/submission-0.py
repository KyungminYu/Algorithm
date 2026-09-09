class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        graph = defaultdict(list)
        for time in times:
            graph[time[0]].append((time[1], time[2]))
        pq = []
        heapq.heappush(pq, (0, k))
        visited = set()
        c_time = 0
        while pq:
            time, node = heapq.heappop(pq)
            if node in visited:
                continue
            visited.add(node)
            c_time = time
            for nxt_node, nxt_time in graph[node]:
                if nxt_node not in visited:
                    heapq.heappush(pq, (time + nxt_time, nxt_node))

        return c_time if len(visited) == n else -1