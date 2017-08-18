#include <stdio.h>

const int MOD = 9901;
int dp[100001][3];
int main(){
    int n; scanf("%d", &n);
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MOD;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
    }
    printf("%d\n", (dp[n][0] + dp[n][1] + dp[n][2]) % MOD);
    return 0;
}