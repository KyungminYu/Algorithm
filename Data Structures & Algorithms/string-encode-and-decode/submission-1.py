class Solution:

    def encode(self, strs: List[str]) -> str:
        if not strs:
            return ""
        res = self.getHashFromStr(strs[0])
        for s in strs[1:]:
            res += "#"
            res += self.getHashFromStr(s)
        return res

    def getHashFromStr(self, s: str) -> str:
        base = 257
        hashVal = 0
        for c in s:
            hashVal *= base
            val = (ord(c) + 1)
            hashVal += val
        return str(hashVal)

    def decode(self, s: str) -> List[str]:
        res = []
        strs = s.split("#")
        for splitedS in strs:
            if not splitedS:
                continue
            res.append(self.getStrFromHash(splitedS))
        return res

    def getStrFromHash(self, hashStr: str) -> str:
        base = 257
        hashVal = int(hashStr)
        s = ""
        
        while hashVal > 0:
            val = hashVal % base
            hashVal //= base
            s = (chr(val - 1)) + s
        
        return s

