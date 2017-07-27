#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const long long INF = 1e17;
int c, p, pb, pa1, pa2, u, v;
long long w;
vector<pair<int, long long> > G[100001];
long long dist[100001];
void dijkstra(int s){
    for(int i = 1; i <= p; i++) dist[i] = INF;
    priority_queue<pair<long long, int> > pq;
    dist[s] = 0;
    pq.push({-dist[s], s});
    while(!pq.empty()){
        int cur = pq.top().second;
        long long cst = -pq.top().first;
        pq.pop();
        if(cst > dist[cur]) continue;
        for(int i = 0; i < G[cur].size(); i++){
            int nxt = G[cur][i].first;
            int ncst = G[cur][i].second;
            if(dist[cur] + ncst < dist[nxt]){
                dist[nxt] = dist[cur] + ncst;
                pq.push({-dist[nxt], nxt});
            }
        }
    }
}
int main(){
    scanf("%d %d %d %d %d", &c, &p, &pb, &pa1, &pa2);
    for(int i = 0; i < c; i++){
        scanf("%d %d %lld", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    };
    dijkstra(pb);
    long long cost = min(dist[pa1], dist[pa2]);
    dijkstra(pa2);
    cost += dist[pa1];
    printf("%lld\n", cost);
    return 0;
}