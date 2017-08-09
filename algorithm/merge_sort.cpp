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