class Solution:
    def foreignDictionary(self, words: List[str]) -> str:
        n = len(words)       
        graph = defaultdict(set)
        indegree = {
            ch: 0
            for word in words
            for ch in word
        }
        for idx1 in range(n - 1):
            w1 = words[idx1]
            w2 = words[idx1 + 1]
            l1 = len(w1)
            l2 = len(w2)
            minL = min(l1, l2)
            if w1[:minL] == w2[:minL] and l1 > l2:
                return ""
            for idx2 in range(minL):
                ch1 = w1[idx2]
                ch2 = w2[idx2]
                if ch1 == ch2:
                    continue
                if ch2 not in graph[ch1]:
                    graph[ch1].add(ch2)
                    indegree[ch2] += 1
                break
        q = deque()
        for key in indegree.keys():
            if indegree[key] == 0:
                q.append(key)
        orders = []
        while q:
            cur = q.popleft()
            orders.append(cur)
            for nxt in graph[cur]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    q.append(nxt)
        if len(orders) != len(indegree):
            return ""
        return "".join(orders)
