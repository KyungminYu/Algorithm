#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int n, m, a, b, c;
vector<pair<int, int> > G[1001];
priority_queue<pair<int, int> > pq;
int toFrom[1001];
int dist[1001];
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &a, &b, &c);
        G[a].push_back({c, b});
        G[b].push_back({c, a});
    }
    for(int i = 0; i <= n; i++) dist[i] = INF;

    dist[1] = 0;
    pq.push({-dist[1], 1});
    while(!pq.empty()){
        int cur = pq.top().second;
        int cst = -pq.top().first;
        pq.pop();
        if(cst > dist[cur]) continue;
        for(int i = 0; i < G[cur].size(); i++){
            int nxt = G[cur][i].second;
            int ncst = G[cur][i].first;
            if(dist[cur] + ncst < dist[nxt]){
                dist[nxt] = dist[cur] + ncst;
                pq.push({-dist[nxt], nxt});
                toFrom[nxt] = cur;
            }
        }
    }
    printf("%d\n", n - 1);
    for(int i = 2; i <= n; i++)
        printf("%d %d\n", i, toFrom[i]);
    
    return 0;
}