class MinStack:
    # Pass Two Stack

    def __init__(self):
        self.stk = []
        self.minStk = []
        
    def push(self, val: int) -> None:
        self.stk.append(val)
        if len(self.minStk) == 0:
            self.minStk.append(val)
        else:
            minVal = min(val, self.getMin())
            self.minStk.append(minVal)

    def pop(self) -> None:
        self.stk.pop()
        self.minStk.pop()

    def top(self) -> int:
        return self.stk[-1]

    def getMin(self) -> int:
        return self.minStk[-1]

        
