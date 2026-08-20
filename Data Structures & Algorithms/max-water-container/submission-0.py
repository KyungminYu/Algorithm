class Solution:
    def maxArea(self, heights: List[int]) -> int:
        res = 0
        l = len(heights)
        left = 0
        right = l - 1

        while left < right:
            width = right - left
            height = min(heights[left], heights[right])
            area = width * height
            res = max(res, area)

            if heights[left] < heights[right]:
                left += 1
            else:
                right -= 1

        return res
        