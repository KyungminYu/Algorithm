class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        # PASS: Counting
        count = [0] * 10001
        mask = 0
        for num in nums:
            count[num] += 1
            if count[num] > 1:
                return num
        return -1