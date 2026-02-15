class Solution:
    def canJump(self, nums: List[int]) -> bool:
        l = len(nums)
        current_end = 0
        reached_end = 0
        for pos in range(l):
            reached_end = max(reached_end, pos + nums[pos])
            if pos == current_end:
                current_end = reached_end
        return l - 1 <= current_end