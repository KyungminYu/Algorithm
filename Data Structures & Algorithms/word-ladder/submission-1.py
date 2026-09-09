class Node:
    def __init__(val: str):
        self.val = val
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList:
            return 0
        q = deque([(beginWord, 1)])
        if beginWord in wordList:
            wordList.remove(beginWord)

        while q:
            word, dist = q.popleft()

            if word == endWord:
                return dist

            chars = list(word)

            for wIdx in range(len(word)):
                original = word[wIdx]
                for cOrd in range(ord('a'), ord('z') + 1):
                    replace = chr(cOrd)
                    if original == replace:
                        continue
                    chars[wIdx] = replace
                    nxt = ''.join(chars)

                    if nxt in wordList:
                        q.append((nxt, dist + 1))
                        wordList.remove(nxt)
                    chars[wIdx] = original

        return 0