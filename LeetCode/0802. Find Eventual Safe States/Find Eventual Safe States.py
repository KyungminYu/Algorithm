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