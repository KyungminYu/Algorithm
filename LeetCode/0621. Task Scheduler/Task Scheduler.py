class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        # I use max heap and greedy to solve this problem
        # First, count all tasks frequency
        count = Counter(tasks)
        pq = []
        # And put it max heap with it's count and key        
        for task in count:
            heapq.heappush(pq, [-count[task], task])

        time = 0
        lastTaskDone = {}
        blockedTasks = {}

        # Second, until pq is valid or blocked Tasks are remained, 
        while pq or blockedTasks:
            # Suppose each loop means 1 time unit.
            time += 1

            # As a greedy algorithm, handle blocked tasks first, and if they are valid at this time slice, it would be removed from block
            for bTask in list(blockedTasks):
                lastDone = lastTaskDone[bTask]
                if n < time - lastDone:
                    heapq.heappush(pq, [-blockedTasks[bTask], bTask])       
                    blockedTasks.pop(bTask)
            # if pq is empty and blocked Tasks are remained, then it means ideal
            # if pq and blocked Tasks are empty, it means end of loop.
            if not pq:
                continue

            # Third pop the task that has max count.
            val = heapq.heappop(pq)
            task = val[1]
            count = -val[0] - 1

            # update last task done time and put it to the blockedTasks if remained count exist
            lastTaskDone[task] = time
            if count > 0:
                blockedTasks[task] = count

        return time