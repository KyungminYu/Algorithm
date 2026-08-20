class Solution:
    def trap(self, height: List[int]) -> int:
        l = len(height)
        lmax = [0] * l
        rmax = [0] * l
        vMax = -1
        for idx in range(l):
            vMax = max(vMax, height[idx])
            lmax[idx] = vMax

        vMax = -1
        for idx in range(l - 1, -1, -1):
            vMax = max(vMax, height[idx])
            rmax[idx] = vMax

        res = 0
        for idx in range(l):
            res += (min(lmax[idx], rmax[idx]) - height[idx])

        return res
