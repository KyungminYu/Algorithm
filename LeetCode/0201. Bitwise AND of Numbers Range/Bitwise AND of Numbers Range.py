# Use bitwise manipulation to keep the common upper binary prefix of left and right, and fill the remaining lower bits with 0.
# Any bit position that differs between left and right changes across [left, right], so its bitwise AND becomes 0.

class Solution:
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        shift = 0
        while left < right:
            left >>= 1
            right >>= 1
            shift += 1
        return left << shift
