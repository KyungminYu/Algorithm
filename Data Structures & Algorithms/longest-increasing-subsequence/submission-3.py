class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        # To solve this problem, I will use binary search to maintain an array called lis.
        # The lis array represent the LIS that has the smallest possible ending value.
        # If the current number is greater than the last element, append it to lis.
        # Otherwise, find the first element greater than or equal to the current number and replace it.
        # Time complexity: O(n log n)
        # Space complexity: O(n)


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