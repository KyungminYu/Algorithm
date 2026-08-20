class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        l1 = len(s1)
        l2 = len(s2)
        if l1 > l2:
            return False

        count1 = [0] * 26
        count2 = [0] * 26
        for c in s1:
            count1[ord(c) - ord('a')] += 1

        for idx in range(l1):
            count2[ord(s2[idx]) - ord('a')] += 1

        for idx in range(l1, l2):
            if count1 == count2:
                return True
            count2[ord(s2[idx]) - ord('a')] += 1
            count2[ord(s2[idx - l1]) - ord('a')] -= 1

        return count1 == count2
        