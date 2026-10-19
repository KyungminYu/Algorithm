class Solution:
    def maxArea(self, heights: List[int]) -> int:
        # To address this problem, I will burrow binary search concept

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
        