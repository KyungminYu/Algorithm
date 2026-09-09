class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        graph = defaultdict(list)
        for ticket in sorted(tickets, reverse = True):
            graph[ticket[0]].append(ticket[1])

        stack = ["JFK"]
        res = []

        while stack:
            cur = stack[-1]
            if graph[cur]:
                stack.append(graph[cur].pop())
            else:
                res.append(stack.pop())

        return res[::-1]