class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        cache = {}
        for idx, num in enumerate(nums):
            req = target - num
            if req in cache:
                return [cache[req], idx]
            cache[num] = idx
        return []
        