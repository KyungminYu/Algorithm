class Solution:

    def str_to_hash(self, s: str) -> str:
        base = 257
        h = 0
        for ch in s:
            h *= base
            h += ord(ch)
        return str(h)
    
    def hash_to_str(self, hStr: str) -> str:
        base = 257
        h = int(hStr)
        s = ""
        while h:
            s = chr(h % base) + s
            h //= base
        return s

    def encode(self, strs: List[str]) -> str:
        if len(strs) == 0:
            return ""
        res = self.str_to_hash(strs[0])
        for s in strs[1:]:
            res += "#"
            res += self.str_to_hash(s)
        return res

    def decode(self, s: str) -> List[str]:
        if len(s) == 0:
            return []
        tokens = s.split("#")
        res = []
        for token in tokens:
            res.append(self.hash_to_str(token))
        return res