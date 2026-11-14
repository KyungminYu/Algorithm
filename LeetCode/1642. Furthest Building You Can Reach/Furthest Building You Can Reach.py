class Solution:
    def furthestBuilding(self, heights: list[int], bricks: int, ladders: int) -> int:
        # I use min heap and greedy approach to solve it

        # First, I calculate a diff of each neighboring building.
        # Second, If the diff is not positive, I can reach next building
        # Third, If not, then put diff to the min heap, and compare length of climbs with num of ladders.
        # Forth, if length of climbs is larger than num of ladders, then I have to pop smallest diff and handle it as a bricks
        # Fifth, if bricks is insufficient, I can not move to next building so I return current position.
        # Repeat Second to Fifth until idx is smaller than n - 2

        n = len(heights)
        climbs = []
        for idx in range(0, n - 1):
            diff = heights[idx + 1] - heights[idx]

            if diff <= 0:
                continue

            heapq.heappush(climbs, diff)

            if len(climbs) > ladders:
                smallestDiff = heapq.heappop(climbs)
                bricks -= smallestDiff
            if bricks < 0:
                return idx

        return n - 1