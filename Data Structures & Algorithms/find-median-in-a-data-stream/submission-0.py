class MedianFinder:

    def __init__(self):
        self.leftMax = []
        self.rightMin = []

    def addNum(self, num: int) -> None:
        if self.leftMax and num > self.leftMax[0]:
            heapq.heappush(self.leftMax, num)
        else:
            heapq.heappush(self.rightMin, -num)

        if len(self.rightMin) > len(self.leftMax) + 1:
            val = heapq.heappop(self.rightMin)
            heapq.heappush(self.leftMax, -val)

        if len(self.leftMax) > len(self.rightMin) + 1:
            val = -heapq.heappop(self.leftMax)
            heapq.heappush(self.rightMin, val)

    def findMedian(self) -> float:
        if len(self.rightMin) > len(self.leftMax):
            return -self.rightMin[0]
        elif len(self.leftMax) > len(self.rightMin):
            return self.leftMax[0]
        return (-self.rightMin[0] + self.leftMax[0]) / 2.0