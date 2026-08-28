class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        
        taskCounts = {}
        for task in tasks:
            taskCounts[task] = taskCounts.get(task, 0) + 1
        
        pq = []
        for task in taskCounts:
            heapq.heappush(pq, -taskCounts[task])

        coolDownInfo = deque()

        time = 0
        while pq or coolDownInfo:
            if pq:
                time += 1
            else:
                time = coolDownInfo[0][0]

            while coolDownInfo and coolDownInfo[0][0] <= time:
                _, coolDowntime = coolDownInfo.popleft()
                heapq.heappush(pq, -coolDowntime)
            
            if pq:
                count = -heapq.heappop(pq) - 1
                if 0 < count:
                    coolDownInfo.append([time + n + 1, count])

        return time
