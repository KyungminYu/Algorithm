class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        res = 0
        current = 0
        prefixSums = { 0 : 1 }

        for num in nums:
            current += num
            diff = current - k

            res += prefixSums.get(diff, 0)
            prefixSums[current] = 1 + prefixSums.get(current, 0)

        return res