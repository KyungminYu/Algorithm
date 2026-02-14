```
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        merged_list = []
        n = len(nums1)
        n_idx = 0
        m = len(nums2)
        m_idx = 0
        while n_idx < n and m_idx < m:
            if nums1[n_idx] < nums2[m_idx]:
                merged_list.append(nums1[n_idx])
                n_idx = n_idx + 1
            else:
                merged_list.append(nums2[m_idx])
                m_idx = m_idx + 1
        while n_idx < n:
            merged_list.append(nums1[n_idx])
            n_idx = n_idx + 1
        while m_idx < m:
            merged_list.append(nums2[m_idx])
            m_idx = m_idx + 1
        merged_len = len(merged_list)
        mid_idx = merged_len // 2
        if merged_len % 2 == 0:
            return (merged_list[mid_idx - 1] + merged_list[mid_idx]) / 2
        else:
            return merged_list[mid_idx]
```

To solve this issue, I can use merge sort technique's merge logic.
First, define merged_list object.
Second, compare nums1[n_idx] and nums2[m_idx] 
Third, append smaller one to the merged_list and increase index of the list that contains smaller value. 
Then, repeat n_idx or m_idx are smaller than their list size.
if repeat is end, append remained lists contents to the merged_list.
Finally, return merged_list's median value.

But, we can run faster than this logic if we use binary search.

```
```