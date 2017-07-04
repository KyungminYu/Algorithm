#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> tree[100001];
int parent[100001][20];
int depth[100001];
int n, m, u, v;
void dfs(int v, int pre, int d){
	parent[v][0] = pre;
	depth[v] = d;
	for(int i = 0; i < tree[v].size(); i++){
		int nxt = tree[v][i];
		if(nxt == pre) continue;
		dfs(nxt, v, d + 1);
	}
}
int getLCA(int u, int v){
	if(depth[u] > depth[v]) swap(u, v);
	int diff = depth[v] - depth[u];
	int i = 0;
	while(diff){
		if(diff & (1 << i)){
			diff -= (1 << i);
			v = parent[v][i];
		}
		i++;
	}
	if(u == v) return u;
	for(i = 19; i >= 0; i--){
		if(parent[u][i] != parent[v][i]){
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}
int main(){
	scanf("%d", &n);
	memset(parent, -1, sizeof(parent));
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	dfs(1, -1, 0);
	for(int i = 1; i < 20; i++){
		for(int j = 1; j <= n; j++){
			int root = parent[j][i - 1];
			if(root == -1) parent[j][i] = -1;
			else parent[j][i] = parent[root][i - 1];
		}
	}

	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		scanf("%d %d", &u, &v);
		printf("%d\n", getLCA(u, v));
	}
	return 0;
}