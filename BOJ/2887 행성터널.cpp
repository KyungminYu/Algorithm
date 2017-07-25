#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int parent[100001];
pair<int, int> x[100001], y[100001], z[100001];
vector<pair<int, pair<int, int> > > G;
int n, cost;

int find(int u){
    if(u == parent[u]) return parent[u];
    return parent[u] = find(parent[u]);
}
void Union(int u, int v, int cst){
    u = find(u); v = find(v);
    if(1 <= n && u != v){
        parent[v] = u;
        cost += cst;
    }
}
int cmp(pair<int, int> &p1, pair<int, int> &p2){
    if(p1.first < p2.first) return 1;
    return 0;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &x[i].first, &y[i].first, &z[i].first);
        x[i].second = y[i].second = z[i].second = i;
        parent[i] = i;
    }
    sort(x, x + n, cmp); sort(y, y + n, cmp); sort(z, z + n, cmp);
    for(int i = 0; i < n - 1; i++){
        G.push_back({x[i + 1].first - x[i].first, {x[i].second, x[i + 1].second}});
        G.push_back({y[i + 1].first - y[i].first, {y[i].second, y[i + 1].second}});
        G.push_back({z[i + 1].first - z[i].first, {z[i].second, z[i + 1].second}});
    }
    sort(G.begin(), G.end());
    for(int i = 0; i < G.size(); i++){
        int cst = G[i].first;
        int u = G[i].second.first;
        int v = G[i].second.second;
        Union(u, v, cst);
    }
    printf("%d\n", cost);
    return 0;
}