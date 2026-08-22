class TimeMap:

    def __init__(self):
        self.info = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.info[key].append([timestamp, value])

    def get(self, key: str, timestamp: int) -> str:
        targetVals = self.info[key]
        l = 0
        r = len(targetVals) - 1
        res = ""
        while l <= r:
            m = (l + r) // 2
            if targetVals[m][0] <= timestamp:
                l = m + 1
                res = targetVals[m][1]
            else:
                r = m - 1
        return res
