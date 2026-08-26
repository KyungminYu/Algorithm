class KthLargest:

    def __init__(self, k: int, nums: List[int]):
        self.k = k
        self.pq = []

        for num in nums:    
            heapq.heappush(self.pq, num)

    def add(self, val: int) -> int:
        heapq.heappush(self.pq, val)
        while len(self.pq) > self.k:
            heapq.heappop(self.pq)
        return self.pq[0]