#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int parent[MAXN][20];
int depth[MAXN];
int score[MAXN];
int cnt[MAXN];
map<pair<int, int>, int> mp;
void dfs(int v, int pre, int d){
    parent[v][0] = pre;
    depth[v] = d;
    for (int i = 0; i < tree[v].size(); i++){
        int nxt = tree[v][i];
        if (nxt == pre) continue;
        dfs(nxt, v, d + 1);
        score[v]+=score[nxt];
    }
    int s = score[v];
    if(v > pre) swap(v, pre);
    if(v != -1) cnt[mp[make_pair(v, pre)]] = s;
}

int getLCA(int u, int v){
    if (depth[u] > depth[v]) swap(u, v);
    int diff = depth[v] - depth[u];
    int i = 0;
    while (diff){
        if (diff & (1 << i)){
            diff -= (1 << i);
            v = parent[v][i];
        }
        i++;
    }
    if (u == v) return u;
    for (i = 19; i >= 0; i--){
        if (parent[u][i] != parent[v][i]){
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
int main(){
    int n, u, v;
    scanf("%d", &n);
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < n - 1; i++){
        scanf("%d %d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
        if (u > v) swap(u, v);
        mp[make_pair(u, v)] = i;
    }

    dfs(1, -1, 0);
    for (int i = 1; i < 20; i++){
        for (int j = 1; j <= n; j++){
            int root = parent[j][i - 1];
            if (root == -1) parent[j][i] = -1;
            else parent[j][i] = parent[root][i - 1];
        }
    }
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++){
        scanf("%d %d", &u, &v);
        int lca = getLCA(u, v);
        score[u]++;
        score[v]++;
        score[lca]-=2;
    }
    dfs(1, -1, 0);
    for (int i = 0; i < mp.size(); i++) printf("%d ", cnt[i]);

    return 0;
}