#include <stdio.h>
int range[501];
int main(){
    int n, m, k; scanf("%d %d %d", &n, &m, &k);
    if(n < m + k - 1 || m * k < n) {
        printf("-1\n"); 
        return 0;
    }
    int mCnt = 0, N = n, M = m, K = k;
    range[mCnt++] = K;
    N -= K; M--;
    while(0 < M){
        if(N % M == 0) break;
        range[mCnt] = N / M;
        N -= range[mCnt];
        M--; mCnt++;
    }
    for(; mCnt < m; mCnt++) range[mCnt] = N / M;
    for(int i = 1, mCnt = 0; i <= n; i += range[mCnt], mCnt++) {
        for(int j = i + range[mCnt] - 1; j >= i; j--) 
            printf("%d ", j);
    }
    return 0;
}