class MinStack:
    # TLE 

    def __init__(self):
        self.stk = []
        
    def push(self, val: int) -> None:
        self.stk.append(val)

    def pop(self) -> None:
        self.stk.pop()

    def top(self) -> int:
        return self.stk[-1]

    def getMin(self) -> int:
        tmpStk = []
        minVal = self.stk[-1]
        while len(self.stk):
            minVal = min(minVal, self.stk[-1])
            tmpStk.append(self.stk.pop())
        while len(tmpStk):
            self.stk.append(tmpStk.pop())

        return minVal

        
