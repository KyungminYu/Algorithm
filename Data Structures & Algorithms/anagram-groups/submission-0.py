class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        maps = defaultdict(list)
        for s in strs:
            k = "".join(sorted(s))
            maps[k].append(s)
        return list(maps.values())