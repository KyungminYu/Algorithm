#include <stdio.h>
const int INF = 0x3f3f3f3f;
int dp[100] = {0, };
int coins[] = {1, 10 ,25};
int main(){
	int T; scanf("%d", &T);
	dp[0] = 0;
	for(int i = 1; i <= 99; i++){
		dp[i] = INF;
		for(int j = 0; j < 3; j++){
			if(i - coins[j] < 0) continue;
			dp[i] = dp[i] < (dp[i - coins[j]] + 1) ? dp[i] : (dp[i - coins[j]] + 1);
		}
	}
	while(T--){
		long long n; scanf("%lld", &n);
		int res = 0;
		while(n){
			res += dp[n % 100];
			n /= 100;
		}
		printf("%d\n", res);
	}
	return 0;
}