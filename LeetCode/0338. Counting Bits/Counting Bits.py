# I will use DP for simulating bit patter.
# Each new block of size l is formed by prepending a leading '1' bit to the previous l numbers, so each popcount increases by 1.
# Its time complexity is O(n) because each element is appended once across doubling steps.
# and space complexity is O(n) for the output array res (excluding the output: O(1)).
class Solution:
    def countBits(self, n: int) -> list[int]:
        res = [0]
        while len(res) <= n:
            l = len(res)
            for i in range(l):
                res.append(res[i] + 1)
        return res[:n + 1]