#include <stdio.h>


int search(int* nums, int numsSize, int target) {
    int low = 0;
    int high = numsSize - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) {
            if (target < nums[mid] && nums[low] <= target) { // ���� ����
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        else {
            if (nums[mid] < target && target <= nums[high]) { // ���� ����
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

int nums[] = { 4,5,6,7,0,1,2 };
int numSize = 7;
int target = 0;
int main() {
    printf("%d\n ", search(nums, numSize, target));
    return 0;
}