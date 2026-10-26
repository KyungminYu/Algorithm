class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        counter = Counter(nums)
        n = len(nums)
        pivot = n // 3
        res = []
        for info in counter:
            val = counter[info]
            if val > pivot:
                res.append(info)
        return res