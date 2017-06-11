#include <stdio.h>
int t[501][501];
int dp[501][501];
int max(int a, int b){
	if(a > b) return a;
	return b;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n;i++){
		for(int j = 1; j <= i; j++) scanf("%d", &t[i][j]);
	}
	dp[1][1] = t[1][1];
	for(int i = 2; i <= n;i++){
		dp[i][1] = dp[i - 1][1] + t[i][1];
		for(int j = 2; j <= i; j++) {
			dp[i][j] = max(dp[i - 1][j] + t[i][j], dp[i - 1][j - 1] + t[i][j]);
		}
	}
	int MAX = dp[n][1];
	for(int i = 2; i <= n;i++)	MAX = max(MAX, dp[n][i]);
	printf("%d\n", MAX);
	return 0;
}	