class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        # PASS: Stack
        psSet = []
        l = len(position)
        for idx in range(l):
            psSet.append([position[idx], speed[idx]])
        psSet.sort()
        
        stk = []
        for idx in range(l - 1, -1, -1):
            time = (target - psSet[idx][0]) / psSet[idx][1]
            stk.append(time)
            if len(stk) >= 2 and stk[-1] <= stk[-2]:
                stk.pop()
        return len(stk)
        