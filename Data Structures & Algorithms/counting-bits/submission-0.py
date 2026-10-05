class Solution:
    def countBits(self, n: int) -> List[int]:
        bits = [0]
        while len(bits) <= n + 1:
            l = len(bits)
            for idx in range(l):
                bits.append(bits[idx] + 1)

        return bits[: n + 1]