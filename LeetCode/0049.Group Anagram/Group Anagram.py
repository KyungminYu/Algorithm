class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        data = {}
        for s in strs:
            sorted_s = "".join(sorted(s))

            if sorted_s not in data:
                data[sorted_s] = []

            data[sorted_s].append(s)

        return list(data.values())