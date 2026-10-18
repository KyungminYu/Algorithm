class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        count = 0
        for num in nums:
            count += (512 ** num)
            
        count2 = count // (512 ** 2)
        count1 = (count - count2 * 512 ** 2) // 512
        count0 = (count - count2 * 512 ** 2 - count1 * 512)

        idx = 0
        while idx < count0:
            nums[idx] = 0
            idx += 1
        while idx < count0 + count1:
            nums[idx] = 1
            idx += 1
        while idx < count0 + count1 + count2:
            nums[idx] = 2
            idx += 1