class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        left = 0
        right = len(numbers) - 1

        while left < right:
            while left < right and target < numbers[left] + numbers[right]:
                right -= 1
            if target == numbers[left] + numbers[right]:
                return [left + 1, right + 1]
            left += 1
        return []