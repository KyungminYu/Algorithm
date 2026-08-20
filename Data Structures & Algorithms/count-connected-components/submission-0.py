class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        vertexes = [[] for _ in range(n)]
        for edge in edges:
            vertexes[edge[0]].append(edge[1])
            vertexes[edge[1]].append(edge[0])

        visited = [False for _ in range(n)]
        
        def traverse(v: int):
            visited[v] = True

            for other in vertexes[v]:
                if visited[other]:
                    continue
                traverse(other)

        res = 0
        for v in range(n):
            if visited[v]:
                continue
            traverse(v)
            res += 1


        return res