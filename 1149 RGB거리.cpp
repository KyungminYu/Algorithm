#include <stdio.h>
int p[1001][4];
int dp[1001][4];
int min(int a, int b){
	if(a < b) return a;
	return b;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n;i++)
		scanf("%d %d %d", &p[i][1], &p[i][2], &p[i][3]);
	dp[1][1] = p[1][1];dp[1][2] = p[1][2];dp[1][3] = p[1][3];
	for(int i = 2; i <= n; i++){
		dp[i][1] = min(dp[i - 1][2] + p[i][1], dp[i - 1][3] + p[i][1]);
		dp[i][2] = min(dp[i - 1][1] + p[i][2], dp[i - 1][3] + p[i][2]);
		dp[i][3] = min(dp[i - 1][1] + p[i][3], dp[i - 1][2] + p[i][3]);
	}
	int MIN = min(dp[n][1], min(dp[n][2], dp[n][3]));
	printf("%d\n", MIN);
	return 0;
}	