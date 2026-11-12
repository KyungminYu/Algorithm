```
class Solution:
    def eventualSafeNodes(self, graph: list[list[int]]) -> list[int]:
        n = len(graph)
        state = [0] * n

        def solve(current: int) -> bool:
            if state[current] != 0:
                return state[current] == 2
            state[current] = 1
            for nxt in graph[current]:
                if not solve(nxt):
                    return False
            state[current] = 2
            return True

        res = []
        for current in range(n):
            if solve(current):
                res.append(current)
        return res
```

I use dfs. First, I define all nodes state 
0 means unvisited, 1 means still in search, and 2 means safe
if I visit already visited, it has two options. One is state 1 that means cycle, the other is state 2 that means safe
This logics' time complexity is O(n + v) and Space complexity is also O(n)