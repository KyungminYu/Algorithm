
#include <stdio.h>

// dp[n][k][0] = dp[n - 1][k][0] + dp[n - 1][k][1]
// dp[n][k][1] = dp[n - 1][k][0] + dp[n - 1][k - 1][1];

int dp[101][101][2];
int main(){
	int t; scanf("%d", &t);
	dp[1][0][0] = dp[1][0][1] = 1;
	for(int i = 0; i <= 99; ++i){
		for(int j = 2; j <= 100; ++j){
			dp[j][i][0] = dp[j - 1][i][0] + dp[j - 1][i][1];
			dp[j][i][1] = dp[j - 1][i][0] + (i ? dp[j - 1][i - 1][1] : 0);
		}
	}
	while(t--){
		int n, k; scanf("%d %d", &n, &k);
		printf("%d\n", dp[n][k][0] + dp[n][k][1]);
	}

	return 0;
}