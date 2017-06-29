#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 40005;
vector<pair<int, long long> > tree[MAXN];
int parent[MAXN][20];
int depth[MAXN];
long long dist[MAXN];

void dfs(int v, int pre, int dep, int dis){
	depth[v] = dep;
	dist[v] = dis;
	parent[v][0] = pre;
	for(int i = 0; i < tree[v].size(); i++){
		int nxt = tree[v][i].first;
		long long cost = tree[v][i].second;
		if(nxt == pre) continue;
		dfs(nxt, v, dep + 1, dis + cost);
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
	if(u == v) return v;
	for(int i = 19; i >=0; i--){
		if(parent[u][i] != parent[v][i]){
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}
long long getDist(int u, int v){
	return dist[u] + dist[v] - 2 * dist[getLCA(u, v)];
}
int main(){
	int N, u, v;
	long long w;
	scanf("%d", &N);

	for(int i = 0; i < N - 1; i++){
		scanf("%d %d %lld", &u, &v, &w);
		tree[u].push_back(make_pair(v, w));
		tree[v].push_back(make_pair(u, w));
	}
	dfs(1, -1, 0, 0);

	for(int i = 1; i <= 19; i++){
		for(int j = 1; j <= N; j++){
			int root = parent[j][i - 1];
			if(root == -1)  parent[j][i] = -1;
			else parent[j][i] = parent[root][i - 1];
		}
	}
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		scanf("%d %d", &u, &v);
		printf("%lld\n", getDist(u, v));
	}
	return 0;
}