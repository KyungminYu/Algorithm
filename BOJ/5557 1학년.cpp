#include <stdio.h>
#define lld long long 
lld in[101], dp[101][21];
int main(){
	lld n; scanf("%lld", &n);
	for(lld i = 1; i <= n; ++i) scanf("%lld", &in[i]);
	dp[1][in[1]] = 1LL;
	for(lld i = 2; i < n; ++i){
		for(lld j = 0; j <= 20; ++j){
			if(j - in[i] >=  0) dp[i][j] += dp[i - 1][j - in[i]];
			if(j + in[i] <= 20) dp[i][j] += dp[i - 1][j + in[i]];
		}
	}
	printf("%lld\n", dp[n - 1][in[n]]);
	return 0;
}