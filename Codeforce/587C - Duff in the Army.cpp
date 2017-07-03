#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int parent[MAXN][20], depth[MAXN];
vector<int> tree[MAXN], c[MAXN], city[MAXN][20], self[MAXN], uVec, vVec, tmp, ans;
void dfs(int v, int pre, int d){
	depth[v] = d;
	parent[v][0] = pre;
	//for(int i = 0; i < 10 && i < c[v].size(); i++) city[v][0].push_back(c[v][i]);
	for(int i = 0; i < tree[v].size(); i++){
		int nxt = tree[v][i];
		if(nxt == pre) continue;
		dfs(nxt, v, d + 1);
	}
}
int getLCA(int u, int v){
	if(depth[u] > depth[v]) swap(v, u);
	int diff = depth[v] - depth[u];
	int i = 0;
	while(diff){
		if(diff & (1 << i)) {
			v = parent[v][i];
			diff -= (1 << i);
		}
		i++;
	}
	if(u == v) return u;
	for(i = 19; i >= 0; i--){
		if(parent[u][i] != parent[v][i]){
			v = parent[v][i];
			u = parent[u][i];
		}
	}
	return parent[u][0];
}
vector<int> merge(vector<int> &v1, vector<int> &v2, int a){
	vector<int> ret(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), ret.begin());
	ret.erase(unique(ret.begin(), ret.end()), ret.end());
	while(ret.size() > a) ret.pop_back();
	return ret;
}
void alloc(vector<int> &dst, vector<int> &src, int a){
	int ind = 0;
	for(int i = 0; i < a && i < src.size(); i++) dst.push_back(src[ind++]);
}
vector<int> kth(int v, int diff, int a){
	vector<int> ret;
	int i = 0;
	while(diff){
		if(diff & (1 << i)){
			vector<int> tmp;
			alloc(tmp, ret, a);
			if(ret.size() == 0)	alloc(ret, city[v][i], a);
			else ret = merge(tmp, city[v][i], a);
			diff -= (1 << i);
			v = parent[v][i];
		}
		i++;
	}
	return ret;
}
int main(){
	int n, m, q, u, v, a, t;
	scanf("%d %d %d", &n, &m, &q);
	memset(parent, -1, sizeof(parent));
	for(int i = 0; i < n - 1; i++){
		scanf("%d %d", &u, &v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	for(int i = 1; i <= m; i++) {
		scanf("%d", &t);
		if(city[v][0].size() > 10) continue; 
		city[v][0].push_back(i);
	}
	dfs(1, -1, 0);
	for(int i = 1; i < 20; i++){
        for(int j = 1; j <= n; j++){  
        	int root = parent[j][i - 1];
            if(root == -1) parent[j][i] = -1;
            else {
            	parent[j][i] = parent[root][i - 1];
            	city[j][i] = merge(city[j][i - 1], city[root][i - 1], 10);
        	}
        }
    }
    for(int i = 0; i < q; i++){
		scanf("%d %d %d", &u, &v, &a);
		int lca = getLCA(u, v);
		uVec = kth(u, depth[u] - depth[lca], a);
		vVec = kth(v, depth[v] - depth[lca], a);
		tmp = merge(uVec, vVec, a);
		ans = merge(tmp, city[lca][0], a);
	
		printf("%d ", ans.size());
		for(int j = 0; j < ans.size(); j++) printf("%d ", ans[j]);
		printf("\n");
    }
	return 0;
}