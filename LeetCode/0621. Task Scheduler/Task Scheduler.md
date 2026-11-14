```
class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        count = Counter(tasks)
        pq = []      
        for task in count:
            heapq.heappush(pq, [-count[task], task])

        time = 0
        lastTaskDone = {}
        blockedTasks = {}

        while pq or blockedTasks:
            time += 1

            for bTask in list(blockedTasks):
                lastDone = lastTaskDone[bTask]
                if n < time - lastDone:
                    heapq.heappush(pq, [-blockedTasks[bTask], bTask])       
                    blockedTasks.pop(bTask)
                    
            if not pq:
                continue
                
            val = heapq.heappop(pq)
            task = val[1]
            count = -val[0] - 1

            lastTaskDone[task] = time
            if count > 0:
                blockedTasks[task] = count

        return time
```

I use max heap and greedy to solve this problem.
First, I count all tasks' count and put it max heap with its count and key  
Second, as a greedy algorithm, handle blocked tasks first, and if they are valid at this time slice, it would be removed from block
Third, if pq is empty and blocked Tasks are remained, then it means idle state. 
Also, if pq and blocked Tasks are empty, it means end of loop.
Forth, I pop the task that has max count, 
update last task done time 
and put it to the blockedTasks if remained count exist

Repeat Second to Forth steps until pq is valid or blocked Tasks are remained 
and I suppose each loop means 1 time unit.

This logic has O(n log n) time complexity and O(n) space complexity