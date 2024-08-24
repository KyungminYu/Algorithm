void merge(int* A, int s, int m, int e){
    int lptr = s, rptr = m + 1, ptr = s;
    int tmp[mmax];
    while(lptr <= m && rptr <= e){
        if(A[lptr] <= A[rptr]) tmp[ptr++] = A[lptr++];
        else tmp[ptr++] = A[rptr++];
    }
    while(lptr <= m)
        tmp[ptr++] = A[lptr++];
    while(rptr <= e)
        tmp[ptr++] = A[rptr++];
    for(int i = s; i <= e; i++)
        A[i] = tmp[i];
}
void msort(int* A, int s, int e){
    if(s >= e) return;
    int mid = (s + e) / 2;
    msort(A, s, mid);
    msort(A, mid + 1, e);
    merge(A, s, mid, e);
}

vector<int> sortArray(vector<int>& nums) {
    int size = nums.size();
    merge_sort(nums, 0, size - 1);
    return nums;
}

void merge(vector<int>& nums, int left, int mid, int right){
    int lIdx = left;
    int rIDx = mid + 1;
    
    int tempIdx = 0;
    int temp[right - left + 1];
    while (lIdx <= mid && rIDx <= right) {
        if(nums[lIdx]<=nums[rIDx]) {
            temp[tempIdx++] = nums[lIdx++];
        } else {
            temp[tempIdx++] = nums[rIDx++];
        }
    }

    int idx = 0;
    if (lIdx > mid) {
        for(idx = rIDx; idx<=right; ++idx) {
            temp[tempIdx++] = nums[idx];
        }
    } else{
        for(idx = lIdx; idx <= mid; ++idx) {
            temp[tempIdx++] = nums[idx];
        }
    }

    for(idx = left; idx <= right; ++idx){
        nums[idx] = temp[idx - left];
    }
}

void merge_sort(vector<int>& nums, int left, int right) {
    if (right <= left) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(nums, left, mid);
    merge_sort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}