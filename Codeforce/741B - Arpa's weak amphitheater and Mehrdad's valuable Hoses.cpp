#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int weight[1001], beauty[1001], gweight[1001], gbeauty[1001], parent[1001];
int dp[1001][1001];
vector<int> grp[1001];
int find(int v){
	if(v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
void Uni(int u, int v){
	u = find(u); v = find(v);
	if(u != v) parent[v] = u;
}
int main(){
	//freopen("input.txt", "r", stdin);
	int n, m, w, u, v, g = 1, size;
	scanf("%d %d %d", &n, &m, &w);
	for(int i = 1; i <= n; i++) parent[i] = i;
	for(int i = 1; i <= n; i++) scanf("%d", &weight[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &beauty[i]);
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &u, &v);
		Uni(u, v);
	}
	for(int i = 1; i <= n; i++){
		int root = find(i);
		grp[root].push_back(i);
		gweight[root] += weight[i];
		gbeauty[root] += beauty[i];
	}	
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= w; j++){
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			if((size = grp[i].size()) == 0) continue;
			if (j + gweight[i] <= w) dp[i][j + gweight[i]] = max(dp[i][j + gweight[i]], dp[i - 1][j] + gbeauty[i]);
			for(int k = 0; k < size; k++){
				if (j + weight[grp[i][k]] <= w) dp[i][j + weight[grp[i][k]]] = max(dp[i][j + weight[grp[i][k]]], dp[i - 1][j] + beauty[grp[i][k]]);
			}
			g = i;			
		}
	}
	printf("%d\n", dp[g][w]); 
	return 0;
}