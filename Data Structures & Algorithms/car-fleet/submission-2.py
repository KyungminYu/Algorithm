class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        # PASS: Iteration
        psSet = []
        l = len(position)
        for idx in range(l):
            psSet.append([position[idx], speed[idx]])
        psSet.sort()
        
        res = 1
        prevArriveTime = (target - psSet[-1][0]) / psSet[-1][1]
        for idx in range(l - 2, -1, -1):
            currentArriveTime = (target - psSet[idx][0]) / psSet[idx][1]
            if currentArriveTime > prevArriveTime:
                prevArriveTime = currentArriveTime
                res += 1
        return res
        