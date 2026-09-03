class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = [0] * numCourses
        graph = [[] for _ in range(numCourses)]
        for pre in prerequisites:
            graph[pre[0]].append(pre[1])
            indegree[pre[1]] += 1

        q = deque()
        for idx in range(numCourses):
            if indegree[idx] == 0:
                q.append(idx)

        while q:
            cur = q.popleft()
            for nxt in graph[cur]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    q.append(nxt)
        for idx in range(numCourses):
            if indegree[idx] != 0:
                return False
        return True