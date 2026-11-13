```
class Solution:
    def search(self, nums: list[int], target: int) -> int:
        n = len(nums)
        l = 0
        r = n - 1

        while l <= r:
            mid = (l + r) // 2
            if nums[mid] == target:
                return mid
            if nums[l] <= nums[mid]:
                if nums[l] <= target < nums[mid]:
                    r = mid - 1
                else:
                    l = mid + 1
            else:
                if nums[mid] < target <= nums[r]:
                    l = mid + 1
                else:
                    r = mid - 1
        return -1
```

I use binary search. 
Since the array is rotated, at least one half is always sorted. 
First, I check which half is sorted. 
Then, if the target is inside that range, I search that half. 
Otherwise, I search the other half. 

The time complexity is O(log n), and the space complexity is O(1).

