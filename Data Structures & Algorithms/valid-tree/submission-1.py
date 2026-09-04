class Solution:
    def validTree(self, n: int, edges: List[List[int]]) -> bool:
        if len(edges) != n - 1:
            return False
        graph = [[] for _ in range(n)]
        for e in edges:
            graph[e[0]].append(e[1])
            graph[e[1]].append(e[0])
        
        visited = {0}
        stack = [0]
        while stack:
            cur = stack.pop()
            
            for nxt in graph[cur]:
                if nxt not in visited:
                    visited.add(nxt)
                    stack.append(nxt)

        return len(visited) == n