class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        k = 0
        for idx in range(len(nums)):
            if nums[idx] != val:
                nums[k] = nums[idx]
                k += 1
        return k