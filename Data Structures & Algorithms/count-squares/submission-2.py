class CountSquares:

    def __init__(self):
        self.pts = []
        self.ptsCnt = defaultdict(int)

    def add(self, point: List[int]) -> None:
        self.pts.append(point)
        self.ptsCnt[tuple(point)] += 1

    def count(self, point: List[int]) -> int:
        res = 0
        px, py = point
        for x, y in self.pts:
            if (abs(py - y) != abs(px - x)) or x == px or y == py:
                continue
            res += self.ptsCnt[(x, py)] * self.ptsCnt[(px, y)]
        return res