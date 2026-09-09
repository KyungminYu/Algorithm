class Node:
    def __init__(val: str):
        self.val = val
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        words = set(wordList)
        if endWord not in words:
            return 0
        
        q = deque([(beginWord, 1)])
        words.discard(beginWord)

        while q:
            word, dist = q.popleft()
            if word == endWord:
                return dist
            
            chars = list(word)
            for idx, original in enumerate(word):
                for code in range(ord('a'), ord('z') + 1):
                    replace = chr(code)
                    if original == replace:
                        continue

                    chars[idx] = replace
                    nxt = ''.join(chars)
                    if nxt in words:
                        q.append((nxt, dist + 1))
                        words.discard(nxt)
                chars[idx] = original

        return 0