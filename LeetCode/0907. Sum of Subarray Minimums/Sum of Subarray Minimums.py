class Solution:
    def sumSubarrayMins(self, arr: list[int]) -> int:
        # I use two monotonic increasing stacks to find the boundary where each element is the minimum.
        # 1. left_sight stores the index of the previous smaller or equal element.
        # 2. right_sight stores the index of the next strictly smaller element.
        # (Using <= on one side and < on the other prevents duplicate counting when values repeat.)
        # The number of subarrays where arr[idx] is the minimum is (idx - left) * (right - idx).
        # Time Complexity: O(n), Space Complexity: O(n)
        n = len(arr)
        left_sight = [-1] * n
        right_sight = [n] * n

        stk = []
        for idx in range(n):
            val = arr[idx]
            while stk and val <= arr[stk[-1]]:
                stk.pop()
            if stk:
                left_sight[idx] = stk[-1]
            stk.append(idx)

        stk = []
        for idx in range(n - 1, -1, -1):
            val = arr[idx]
            while stk and val < arr[stk[-1]]:
                stk.pop()
            if stk:
                right_sight[idx] = stk[-1]
            stk.append(idx)

        MOD = 10 ** 9 + 7
        res = 0
        for idx in range(n):
            val = arr[idx]
            res += ((idx - left_sight[idx]) * (right_sight[idx] - idx) * val)
            res %= MOD

        return res