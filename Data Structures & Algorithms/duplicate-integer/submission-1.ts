class Solution {
    /**
     * @param {number[]} nums
     * @return {boolean}
     */
    hasDuplicate(nums: number[]): boolean {
        var count = new Set()
        for (const num of nums) {
            if (count.has(num)) {
                return true
            }
            count.add(num) 
        }
        return false
    }
}
