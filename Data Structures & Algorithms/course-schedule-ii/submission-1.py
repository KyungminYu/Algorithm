class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        
        inorder = [0] * numCourses
        graph = [[] for _ in range(numCourses)]

        for pre in prerequisites:
            graph[pre[1]].append(pre[0])
            inorder[pre[0]] += 1

        q = deque()
        for idx in range(numCourses):
            if inorder[idx] == 0:
                q.append(idx)

        res = []

        while q:
            cur = q.popleft()
            res.append(cur)
            for nxt in graph[cur]:
                inorder[nxt] -= 1
                if inorder[nxt] == 0:
                    q.append(nxt)

        return res if len(res) == numCourses else []