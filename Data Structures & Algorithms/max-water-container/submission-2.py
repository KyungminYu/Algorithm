class Solution:
    def maxArea(self, heights: List[int]) -> int:
        # To address this problem, I will adopt binary search concept.
        # When I reducing range(left or right), I will check height of each position and change the point that has lower height.
        # Because if lower position have a chance to be higher position.
        # In this regard, I think it seems like greedy algorithm.
        # And then, it's time complexity is O(n), Space Complexity is O(1)


        n = len(heights)
        res = 0
        left = 0
        right = n - 1

        while left < right:
            height = min(heights[left], heights[right])
            width = right - left
            res = max(res, height * width)
            if heights[left] < heights[right]:
                left += 1
            else:
                right -= 1

        return res
        