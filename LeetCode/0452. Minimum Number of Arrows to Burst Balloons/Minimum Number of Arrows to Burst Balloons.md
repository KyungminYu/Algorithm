```
class Solution:
    def findMinArrowShots(self, points: list[list[int]]) -> int:
        points.sort()
        required_arrow = len(points)
        overlap = points[0]
        for p in points[1:]:
            if (overlap[0] <= p[0] <= overlap[1]
             or overlap[0] <= p[1] <= overlap[1]):
                overlap[0] = max(overlap[0], p[0])
                overlap[1] = min(overlap[1], p[1])
                required_arrow -= 1
            else:
                overlap = p
        return required_arrow
```

I use greedy approach to solve it
First, I sort points with its first elements.
Second, I define overlap_count as length of points and overlap with points's first element.
Third, I traverse all points from 2nd element. If p and current overlap is overlapped I update its range as max of first element and min of second element. In this regard, I can find out the target x that I have to shoot.
If not, I initialize overlap as current point.
Finally, I return required_arrow
Its time complexity is O(n log n) and space complexity is O(1) 