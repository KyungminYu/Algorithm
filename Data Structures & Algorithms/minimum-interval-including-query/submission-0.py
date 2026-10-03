class Solution:
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:
        intervals.sort()
        queries = sorted((q, i) for i, q in enumerate(queries))

        res = [-1] * len(queries)
        heap = [] 
        iIdx = 0

        for query, qIdx in queries:
            while iIdx < len(intervals) and intervals[iIdx][0] <= query:
                start, end = intervals[iIdx]
                heapq.heappush(heap, (end - start + 1, end))
                iIdx += 1

            while heap and heap[0][1] < query:
                heapq.heappop(heap)

            if heap:
                res[qIdx] = heap[0][0]

        return res