#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 1e9, NMAX = 51, HMAX = 250000;
int n, in[NMAX], dp[NMAX][HMAX + 1];
int solve(int pos, int diff){
	if(diff > HMAX) return -INF;
	if(pos == n){
		if(diff == 0) return 0;
		return -INF;
	}
	int& ret = dp[pos][diff];
	if(ret != -1) return ret;
	ret = solve(pos + 1, diff);
	ret = max(ret, solve(pos + 1, diff + in[pos]));
	if(diff - in[pos] >= 0) 
		ret = max(ret, solve(pos + 1, diff - in[pos]) + in[pos]);
	else 
		ret = max(ret, solve(pos + 1, in[pos] - diff) + diff); 
	return ret;
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &in[i]);
	memset(dp, -1, sizeof(dp));
	int res = solve(0, 0);
	printf("%d\n", res? res : -1);
	return 0;
}