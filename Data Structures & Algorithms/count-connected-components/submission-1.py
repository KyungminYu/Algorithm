class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        
        parents = []
        for i in range(n):
            parents.append(i)

        def find(i: int) -> int:
            if parents[i] == i:
                return i
            return find(parents[i])

        def union(i: int, j: int):
            ip = find(i)
            jp = find(j)
            parents[ip] = jp
            
        for e in edges:
            union(e[0], e[1])

        res = 0
        count = [0 for _ in range(n)]
        for i in range(n):
            p = find(i)
            count[p] += 1
            if count[p] == 1:
                res += 1
        return res