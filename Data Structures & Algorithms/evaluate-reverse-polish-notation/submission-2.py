class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stk = []
        for t in tokens:
            if t == '+':
                v1 = stk.pop()
                v2 = stk.pop()
                stk.append(v2 + v1)
            elif t == '-':
                v1 = stk.pop()
                v2 = stk.pop()
                stk.append(v2 - v1)
            elif t == '*':
                v1 = stk.pop()
                v2 = stk.pop()
                stk.append(v2 * v1)
            elif t == '/':
                v1 = stk.pop()
                v2 = stk.pop()
                stk.append(int(v2 / v1))
            else:
                stk.append(int(t))
        return stk[-1]