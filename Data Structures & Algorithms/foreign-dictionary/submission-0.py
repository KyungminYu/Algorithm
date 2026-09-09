class Solution:
    def foreignDictionary(self, words: List[str]) -> str:
        
        graph = defaultdict(set)

        indegree = {
            char: 0
            for word in words
            for char in word
        }
        for i in range(len(words) - 1):
            word1 = words[i]
            word2 = words[i + 1]
            l1 = len(word1)
            l2 = len(word2)
            minL = min(l1, l2)
            if word1[:minL] == word2[:minL] and l1 > l2:
                return ""
            for j in range(minL):
                s = word1[j]
                e = word2[j]
                if s == e:
                    continue
                if e not in graph[s]:
                    graph[s].add(e)
                    indegree[e] += 1
                break

        q = deque()
        for ch, indeg in indegree.items():
            if indeg == 0:
                q.append(ch)
        order = []
        while q:
            cur = q.popleft() 
            order.append(cur)
            for nxt in graph[cur]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    q.append(nxt)
        if len(order) != len(indegree):
            return ""
                    
        return ''.join(order)