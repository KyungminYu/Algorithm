class Solution:
    def nextGreaterElements(self, nums: list[int]) -> list[int]:
        # I use a monotonic decreasing stack to store indices of elements that haven't found their next greater element yet.
        # And I iterate twice (2 * n) using modulo to simulate a circular array.
        # them, I pop indices when the current number is greater, and record it in `res`.
        # Time Complexity: O(n), Space Complexity: O(n)
        n = len(nums)
        res = [-1] * n
        stk = []

        for i in range(n * 2):
            idx = i % n
            num = nums[idx]

            while stk and nums[stk[-1]] < num:
                prev = stk.pop()
                res[prev] = num

            if i < n:
                stk.append(idx)

        return res
