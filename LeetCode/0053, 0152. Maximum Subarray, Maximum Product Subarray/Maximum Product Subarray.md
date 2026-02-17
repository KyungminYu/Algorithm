```
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        length = len(nums)
        current_min = nums[0]
        current_max = nums[0]
        res = nums[0]
        for i in range(1, length):
            if nums[i] < 0:
                current_min, current_max = current_max, current_min
            current_max = max(nums[i], current_max * nums[i])
            current_min = min(nums[i], current_min * nums[i])
            res = max(res, current_max)
        return res
```
### GPT revised

I used dynamic programming with rolling variables.

I tracked current_max and current_min, which represent the maximum and minimum product of a subarray ending at index i.
I keep both because a negative number can flip the sign
: the previous min can become the new max, and the previous max can become the new min.

So, before updating, if nums[i] is negative, I swap current_max and current_min.
Then I decide whether to start a new subarray at i (nums[i]) or extend the previous one (current_max * nums[i], current_min * nums[i])
: current_max = max(nums[i], current_max * nums[i])
: current_min = min(nums[i], current_min * nums[i])

Finally, I update res with the best current_max seen so far.
This runs in O(n) time and O(1) space.

### My solution

I used dynamic programming.
I tracked current_max and current_min that are the maximum and minimum subarray's product at index i.
At each element, 
I decided whether it is better to extend previous subarray(current_max * nums[i]) or start a new subarray(nums[i]).
and whether it is better to extend previous subarray(current_min * nums[i]) or start a new subarray(nums[i])
To check minProduct and maxProduct.
Before this action, I check that nums[i] is negative value. 
if it is negative, current_min and current_max would be swapped, I swap current_min and current_max
Then I updated res with the best current_max seen so far.
This runs in O(n) time and O(1) space.