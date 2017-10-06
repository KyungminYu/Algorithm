#pragma GCC optimize("O2")
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int mp[21][21];
int opCost[23];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, m;

int isCan(int r, int c){
	return (0 <= r && r < n && 0 <= c && c < n);
}
int solve(int r, int c, int k){
	int cnt = 0;
	for(int i = -k; i <= k; i++){
		for(int j = -k; j <= k; j++){
			int limit = abs(i) + abs(j);	
			if(limit >= k) continue;
			if(!isCan(r + i, c + j)) continue;
			cnt += mp[r + i][c + j];
		}
	}
	if(m * cnt - opCost[k] >= 0) return cnt;
	return 0;
}
int main(){
	int T; scanf("%d", &T);
	for(int k = 1; k <= 21; k++)
		opCost[k] = k * k + (k - 1) * (k - 1);
	
	for(int t = 1; t <= T; t++){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				scanf("%d", &mp[i][j]);
		}
		int ans = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				for(int k = 1; k <= n + 1; k++)
					ans = max(ans, solve(i, j, k));
			}
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}