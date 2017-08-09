#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;
int n, m, s, e, u, v, w;
int low, high, ans;
vector<pair<int, int> > G[100001];
int chk[100001], weight[100001];
int solve(int v, int limit, int fin){
    if(v == fin) return 1;

    chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i].first;
        int cst = G[v][i].second;
        if(chk[nxt]) continue;
        if(cst < limit) continue;
        if(solve(nxt, limit, fin)) return 1;
    }
    return 0;
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
        weight[i] = w;
    }
    scanf("%d %d", &s, &e);
    sort(weight, weight + m);
    low = 0; high = m - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        memset(chk, 0, sizeof(chk));
        if(solve(s, weight[mid], e)) {
            ans = weight[mid];
            low = mid + 1;
        }
        else high = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}