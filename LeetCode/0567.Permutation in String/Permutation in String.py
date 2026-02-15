class Solution:

    def checkInclusion(self, s1: str, s2: str) -> bool:
        s1_len = len(s1)
        s2_len = len(s2)
        if s2_len < s1_len:
            return False

        s1_count = [0] * 26
        s2_sub_count = [0] * 26

        for idx in range(s1_len):
            s1_count[ord(s1[idx]) - ord('a')] += 1

        for idx in range(s1_len):
            s2_sub_count[ord(s2[idx]) - ord('a')] += 1

        if s1_count == s2_sub_count:
            return True

        for idx in range(s1_len, s2_len):
            s2_sub_count[ord(s2[idx]) - ord('a')] += 1
            s2_sub_count[ord(s2[idx - s1_len]) - ord('a')] -= 1
            if s1_count == s2_sub_count:
                return True

        return False
