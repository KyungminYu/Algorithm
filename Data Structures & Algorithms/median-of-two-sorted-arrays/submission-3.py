class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        n = len(nums1)
        m = len(nums2)

        if n > m:
            n, m = m, n
            nums1, nums2 = nums2, nums1
        
        half = (n + m + 1) // 2
        left = 0
        right = n

        while left <= right:
            # if mid1 is decreased, mid2 would be increased
            mid1 = (left + right) // 2
            mid2 = half - mid1

            nums1Lower = nums1[mid1 - 1] if mid1 > 0 else float("-inf")
            nums1Upper = nums1[mid1] if mid1 < n else float("inf")

            nums2Lower = nums2[mid2 - 1] if mid2 > 0 else float("-inf")
            nums2Upper = nums2[mid2] if mid2 < m else float("inf") 

            # nums1Lower <= nums2Upper
            # nums2Lower <= nums1Upper

            if nums1Lower > nums2Upper:
                right = mid1 - 1
            elif nums2Lower > nums1Upper:
                left = mid1 + 1
            else:
                if (n + m) % 2 == 1:
                    return max(nums1Lower, nums2Lower)
                else:
                    return (max(nums1Lower, nums2Lower) + min(nums1Upper, nums2Upper)) / 2
        return -1
