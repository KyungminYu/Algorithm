#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const long long INF = 1e17;
vector<pair<long long, long long> > G[801];
long long n, e, u, v, w, donetoA, donetoB, dNtoA, dNtoB, dAtoB;
long long dist[801];

long long dijkstra(long long s){
    for(long long i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<pair<long long, long long> > pq;
    pq.push(make_pair(-0, s));
    dist[s] = 0;
    while(!pq.empty()){
        long long cur = pq.top().second;
        pq.pop();
        for(int i = 0; i < G[cur].size(); i++){
            long long nxt = G[cur][i].first;
            long long nxtcst = G[cur][i].second;
            if(dist[cur] + nxtcst < dist[nxt]){
                dist[nxt] = dist[cur] + nxtcst;
                pq.push(make_pair(-dist[nxt], nxt));
            }
        }
    }
}

int main(){
    scanf("%lld %lld", &n, &e);
    for(int i = 0; i < e; i++){
        scanf("%lld %lld %lld", &u, &v, &w);
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }
    scanf("%lld %lld", &u, &v);
    dijkstra(1);
    donetoA = dist[u];
    donetoB = dist[v];
    dijkstra(n);
    dNtoA = dist[u];
    dNtoB = dist[v];
    dijkstra(u);
    dAtoB = dist[v];

    long long oneAB = min(donetoA + dNtoB, donetoB + dNtoA) + dAtoB;
    long long twoAB = min(donetoA + donetoB, dNtoA + dNtoB) + 2 * dAtoB;
    long long ans = min(oneAB, twoAB);
    if(ans >= INF) ans = -1;
    printf("%lld\n", ans);
    return 0;
}