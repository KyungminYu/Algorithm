#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, pair<int, int> > > G;
int n, m, u, v, w, cost;
int parent[100001];
int find(int u){
    if(u == parent[u]) return parent[u];
    return parent[u] = find(parent[u]);
}
void Union(int u, int v, int cst){
    u = find(u);
    v = find(v);
    if(n > 2 && u != v) {
        parent[v] = u;
        cost += cst;
        n--;
    }
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) parent[i] = i;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &u, &v, &w);
        G.push_back({w, {u, v}});
    }
    sort(G.begin(), G.end());
    for(int i = 0; i < G.size(); i++){
        int cst = G[i].first;
        u = G[i].second.first;
        v = G[i].second.second;
        Union(u, v, cst);
    }
    printf("%d\n", cost);
    return 0;
}