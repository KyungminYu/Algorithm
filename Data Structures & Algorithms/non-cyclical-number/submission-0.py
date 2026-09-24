class Solution:
    def isHappy(self, n: int) -> bool:
        def getNext(n) -> int:
            res = 0
            while n:
                res += (n % 10) ** 2
                n = n // 10
            return res

        cache = set()
        cur = n
        while cur != 1:
            if cur in cache:
                return False
            cache.add(cur)
            cur = getNext(cur)
        return True