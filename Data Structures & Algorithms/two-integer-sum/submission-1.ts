class Solution {
    /**
     * @param {number[]} nums
     * @param {number} target
     * @return {number[]}
     */
    twoSum(nums: number[], target: number): number[] {
        const last = new Map<number, number>()
        for (let idx = 0; idx < nums.length; idx++) {
            const value = nums[idx]
            const need = target - value
            if (last.has(need)) {
                return [last.get(need)!, idx]
            }
            last.set(value, idx)
        }
        return []
    }
}
