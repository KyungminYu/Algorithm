class Solution:
    def partitionLabels(self, s: str) -> List[int]:

        lastIndices = {}
        for idx, ch in enumerate(s):
            lastIndices[ch] = idx

        res = []
        partitionStartIdx = 0
        partitionEndIdx = -1
        for idx, ch in enumerate(s):
            lastIndex = lastIndices[ch]
            partitionEndIdx = max(partitionEndIdx, lastIndex)
            if idx == partitionEndIdx:
                res.append(partitionEndIdx - partitionStartIdx + 1)
                partitionStartIdx = idx + 1
        return res