#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int boy[1001], girl[1001], dp[1001][1001];
int main(){
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &boy[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &girl[i]);
	sort(boy + 1,  boy + n + 1), sort(girl + 1, girl + m + 1);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp[i][j] = dp[i - 1][j - 1] + abs(boy[i] - girl[j]);
			if(i > j) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
			if(i < j) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
		}
	}
	printf("%d\n", dp[n][m]);
	return 0;
}