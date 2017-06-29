#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<pair<int, int> > tree[MAXN];
int parent[MAXN][20], MinDP[MAXN][20], MaxDP[MAXN][20];
int depth[MAXN];

void dfs(int v, int pre, int dep){
	depth[v] = dep;
	parent[v][0] = pre;
	for(int i = 0; i < tree[v].size(); i++){
		int nxt = tree[v][i].first;
		int cost = tree[v][i].second;
		if(nxt == pre) continue;
		MaxDP[nxt][0] = MinDP[nxt][0] = cost;
		dfs(nxt, v, dep + 1);
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
int kth(int v, int diff, int type){
	int i = 0;
	int ret = 1e9;
	if(type) ret *= (-1);
	while(diff){
		if(diff & (1 << i)){
			diff -= (1 << i);
			if(type) ret = max(ret, MaxDP[v][i]);
			else ret = min(ret, MinDP[v][i]);
			v = parent[v][i];
		}
		i++;
	}
	return ret;
}
int query(int u, int v, int type){
	int ret;
	int lca = getLCA(u, v);
	if(type){
		ret = -1e9;
		ret = max(kth(u, depth[u] - depth[lca], type), kth(v, depth[v] - depth[lca], type));
	}
	else{
		ret = 1e9;
		ret = min(kth(u, depth[u] - depth[lca], type), kth(v, depth[v] - depth[lca], type));
	}
	return ret;
}
int main(){
	int N, u, v;
	int w;
	scanf("%d", &N);
	memset(MinDP, 0x3f3f3f, sizeof(MinDP));
	memset(MaxDP, -1, sizeof(MaxDP));
	for(int i = 0; i < N - 1; i++){
		scanf("%d %d %d", &u, &v, &w);
		tree[u].push_back(make_pair(v, w));
		tree[v].push_back(make_pair(u, w));
	}
	dfs(1, -1, 0);

	for(int i = 1; i <= 19; i++){
		for(int j = 1; j <= N; j++){
			int root = parent[j][i - 1];
			if(root == -1)  parent[j][i] = -1;
			else parent[j][i] = parent[root][i - 1];
		}
	}
	for(int i = 1; i <= 19; i++){
		for(int j = 1; j <= N; j++){
			int root = parent[j][i - 1];
			if(root == -1) {
				parent[j][i] = -1; 
				MinDP[j][i] = MinDP[j][i - 1];
				MaxDP[j][i] = MaxDP[j][i - 1]; 
			}
			else {
				parent[j][i] = parent[root][i - 1];
				MinDP[j][i] = min(MinDP[j][i - 1], MinDP[root][i - 1]);
				MaxDP[j][i] = max(MaxDP[j][i - 1], MaxDP[root][i - 1]);
			}
		}
	}
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		scanf("%d %d", &u, &v);
		printf("%d %d\n", query(u, v, 0), query(u, v, 1));
	}
	return 0;
}