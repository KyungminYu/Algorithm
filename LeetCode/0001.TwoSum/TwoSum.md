A brute-force approach checks all pairs, which is O(n^2).
```
class Solution(object):
    def twoSum(self, nums, target):
        size = len(nums)
        for i in range(0, size-1):
            for j in range(i+1, size):
                if nums[i] + nums[j] == target:
                    return [i, j]
        return []
```

But, I can do better using a hashmap
I will iterate through the array once.
For each value x at index i, I compute the required number that means target minus x.
If the required num is already in the hash map, I return the stored index and i.
Otherwise, I store value x with index i and continue.
This logic's time complexity is O(n) and space complexity is O(n).

```
class Solution(object):
    def twoSum(self, nums, target):
        cache = {}
        for i, x in enumerate(nums):
            require = target - x
            if require in cache:
                return [cache[require], i]
            cache[x] = i
        return []
```