#include <stdio.h>
const int mod = 1000000007;
int dp[1001];
int main(){
	int n, T = 1;
	dp[0] = dp[1] = dp[2] = 1;
	for (int i = 3; i <= 1000; i++){
		for (int j = 1; j < i; j++){
			if ((i - 1 - j) % j == 0) {
				dp[i] += dp[j];
				dp[i] %= mod;
			}
		}
	}
	while (scanf("%d", &n) != EOF)	printf("Case %d: %d\n", T++, dp[n]);
	return 0;
}