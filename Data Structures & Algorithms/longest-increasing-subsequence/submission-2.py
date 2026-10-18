class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        # To solve this problem, I will use binary search algorithm.
        # First, make lis array for traking lis component.
        # Second, put 1st element of nums to the lis as an initial value.
        # Then, iterate remained nums, we have to skip last element of lis and each num is equal because we do not have to consider them.
        # Also, if each num is larger than last element of lis, append each num to the lis array.
        # Lastly, if each num is smaller than last element of lis, we have to find proper position to put each num to lis by using binary search.
        # Finally, return the length of lis array.
        lis = [nums[0]]
        for num in nums[1:]:
            if lis[-1] == num:
                continue
            if lis[-1] < num:
                lis.append(num)
                continue
            left = 0
            right = len(lis) - 1
            while left <= right:
                mid = (left + right) // 2
                if lis[mid] < num:
                    left = mid + 1
                else:
                    right = mid - 1
            lis[left] = num

        return len(lis)