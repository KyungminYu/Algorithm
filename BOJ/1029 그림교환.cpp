#include <stdio.h>
#define MAXN 15
#define MAX_PRICE 10
int cost[MAXN][MAXN];
int dp[1 << MAXN][MAXN][MAX_PRICE] = { 0, }; 
int n;
int solve(int visit, int from, int c, int d) {
	int& ret = dp[visit][from][c];
	if (ret != 0) return ret;
	ret = d;

	for (int to = 0; to < n; ++to) {
		if (to == from) continue;
		if (c > cost[from][to]) continue;
		if (visit & (1 << to)) continue;
		int tmp = solve((visit | (1 << to)), to, cost[from][to], d + 1);
		ret = ret > tmp ? ret : tmp;
	}

	return ret;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			scanf(" %1d", &cost[i][j]);
	}
	printf("%d\n", solve((1 << 0), 0, 0, 1));

	return 0;
}