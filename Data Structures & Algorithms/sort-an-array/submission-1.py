class Solution:

    def merge(self, nums: List[int], left: int, mid: int, right: int):
        sorted_sub_nums = []
        lIdx = left
        rIdx = mid + 1
        while lIdx <= mid and rIdx <= right:
            if nums[lIdx] < nums[rIdx]:
                sorted_sub_nums.append(nums[lIdx])
                lIdx += 1
            else:
                sorted_sub_nums.append(nums[rIdx])
                rIdx += 1

        while lIdx <= mid:
            sorted_sub_nums.append(nums[lIdx])
            lIdx += 1

        while rIdx <= right:
            sorted_sub_nums.append(nums[rIdx])
            rIdx += 1
        for idx in range(left, right + 1):
            nums[idx] = sorted_sub_nums[idx - left]


    def mergeSort(self, nums: List[int], left: int, right: int):
        if right <= left:
            return
        mid = (left + right) // 2
        self.mergeSort(nums, left, mid)
        self.mergeSort(nums, mid + 1, right)
        self.merge(nums, left, mid, right)


    def sortArray(self, nums: List[int]) -> List[int]:
        self.mergeSort(nums, 0, len(nums) - 1)
        return nums