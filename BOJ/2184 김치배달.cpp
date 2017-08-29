#pragma GCC optimize("O2")
#include <stdio.h>
#define ABS(a) (((a) < 0) ? (-(a)) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
const int MAXN = 1001;
const int INF = 1e9;
int n, m;
int arr[MAXN];
int dp[MAXN][MAXN][2];
void merge(int A[], int l, int m, int r){
    int lptr = l, rptr = m + 1, ptr = 0;
    int tmp[r - l + 1];
    while(lptr <= m && rptr <= r){
        if(A[lptr] < A[rptr]) tmp[ptr++] = A[lptr++];
        else tmp[ptr++] = A[rptr++];
    } 
    while(lptr <= m) tmp[ptr++] = A[lptr++];
    while(rptr <= r) tmp[ptr++] = A[rptr++];
    for(int i = 0; i < ptr; i++) A[l + i] = tmp[i];
}
void msort(int A[], int l, int r){
    if(r <= l) return;
    int mid = (l + r) / 2;
    msort(A, l, mid);
    msort(A, mid + 1, r);
    merge(A, l, mid, r);
}
int solve(int A[], int l, int r, int lr){
    if(l == n && r == 0) return 0;
    if(l >  n || r  < 0) return INF;
    int& ret = dp[l][r][lr];
    if(ret != -1) return ret;
    ret = INF;
    int cnt = n - (l - r);
    if(lr) ret = MIN(solve(A, l, r - 1, 1) + cnt * ABS(A[r] - A[r - 1]), 
                     solve(A, l + 1, r, 0) + cnt * ABS(A[r] - A[l + 1]));
    else   ret = MIN(solve(A, l, r - 1, 1) + cnt * ABS(A[r - 1] - A[l]), 
                     solve(A, l + 1, r, 0) + cnt * ABS(A[l + 1] - A[l]));
    return ret;
}
int main(){
    scanf("%d %d", &n, &m);
    arr[0] = m;
    for(int i = 1; i <= n; i++) scanf("%d", &arr[i]);
    msort(arr, 0, n);
    int sind = 0;
    for(int i = 0; i <= n; i++)
        if(arr[i] == m) sind = i;
    for(int i = 0; i < MAXN; i++){
        for(int j = 0; j < MAXN; j++) dp[i][j][0] = dp[i][j][1] = -1;
    }
    printf("%d\n", solve(arr, sind, sind, 0));
    return 0;
}