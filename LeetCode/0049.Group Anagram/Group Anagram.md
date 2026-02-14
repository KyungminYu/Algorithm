```
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        data = {}
        for s in strs:
            sorted_s = "".join(sorted(s))

            if sorted_s not in data:
                data[sorted_s] = []

            data[sorted_s].append(s)

        return list(data.values())
```

Anagrams share the same characters with the same counts. 
Therefore, if we sort the characters in each string, 
all anagrams will produce the same sorterd result.

I use a dictionary where the key is the sorted string 
and the value is the list of original strings that map to that key.

After processing all strings, I return all dictionary values as the grouped anagrams.

Time complexity is O(n * k log k) on average. Because sorting each string takes O(k log k)
