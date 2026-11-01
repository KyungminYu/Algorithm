class Solution {
    /**
     * @param {string} s
     * @param {string} t
     * @return {boolean}
     */
    isAnagram(s: string, t: string): boolean {
        var count = new Map<string, number>()
        for (const ch of s) {
            if (count.has(ch)) {
                count.set(ch, count.get(ch) + 1)
            } else {
                count.set(ch, 1)
            }
        }
        for (const ch of t) {
            if (count.has(ch)) {
                count.set(ch, count.get(ch) - 1)
                if (count.get(ch) == 0) {
                    count.delete(ch)
                }
            } else {
                count.set(ch, -1)
            }
        }
        return count.size == 0
        
    }
}
