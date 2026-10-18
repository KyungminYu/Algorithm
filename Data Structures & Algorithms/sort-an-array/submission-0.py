class Solution:
    def sortArray(self, nums: List[int]) -> List[int]:
        count = [0] * 100001
        for n in nums:
            count[n + 50000] += 1
        
        res = [] 
        for idx in range(len(count)):
            for c in range(count[idx]):
                res.append(idx - 50000)
        return res