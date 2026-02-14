class Solution(object):
    def twoSum(self, nums, target):
        cache = {}
        for i, x in enumerate(nums):
            require = target - x
            if require in cache:
                return [cache[require], i]
            cache[x] = i
        return []