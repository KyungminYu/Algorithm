#include <stdio.h>

int dp[41];
int main(){
	dp[0] = dp[1] = 1;
	for(int i = 2; i <= 40; ++i)
		dp[i] = dp[i - 1] + dp[i - 2];
	int n, m, v; scanf("%d %d", &n, &m);
	int res = 1, l = 1;
	for(int i = 0, v; i < m; ++i, l = v + 1){
		scanf("%d", &v);
		res *= dp[v - l];		
	}
	res *= dp[n - l + 1];
	printf("%d", res);
	return 0;
}