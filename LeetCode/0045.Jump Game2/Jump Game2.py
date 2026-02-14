class Solution:
    def jump(self, nums: List[int]) -> int:
        length = len(nums)
        res = 0
        current_end = 0
        reached_end = 0
        for pos in range(length - 1):
            reached_end = max(reached_end, pos + nums[pos])

            if pos == current_end:
                res += 1
                current_end = reached_end
        return res