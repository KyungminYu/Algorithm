#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int NMAX = 10001;

vector<pair<int, int> > G[NMAX], R[NMAX];
int indegree[NMAX], chk[NMAX], dist[NMAX];
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        G[a].push_back({b, c});
        R[b].push_back({a, c});
        indegree[b]++;
    }
    int s, e; scanf("%d %d", &s, &e);
    
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < G[cur].size(); i++){
            int nxt = G[cur][i].first;
            int cst = G[cur][i].second;
            dist[nxt] = dist[nxt] > dist[cur] + cst 
                      ? dist[nxt] : dist[cur] + cst;
            if(!(--indegree[nxt])) q.push(nxt);
        }
    }
    
    q.push(e);
    int res = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(chk[cur]) continue;
        chk[cur] = 1;
        for(int i = 0; i < R[cur].size(); i++){
            int nxt = R[cur][i].first;
            int cst = R[cur][i].second;
            if((dist[nxt] + cst) == dist[cur]){
                q.push(nxt);
                res++;
            }
        }
    }
    printf("%d\n%d", dist[e], res);
    return 0;
}