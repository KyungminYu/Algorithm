#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int> > G[10005], R[10005];
int indegree[10005], chk[10005], dist[10005];
int main(){
    int n, m, u, v, w, s, e, cnt;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &u, &v, &w);
        G[u].push_back(make_pair(v, w));
        R[v].push_back(make_pair(u, w));
        indegree[v]++;
    }
    scanf("%d %d", &s, &e);
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < G[cur].size(); i++){
            int nxt = G[cur][i].first;
            int cst = G[cur][i].second;
            dist[nxt] = dist[nxt] > dist[cur] + cst ? dist[nxt] : dist[cur] + cst;
            indegree[nxt]--;
            if(indegree[nxt] == 0) q.push(nxt);
        }
    }
    q.push(e);
    cnt = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(chk[cur]) continue;
        chk[cur] = 1;
        for(int i = 0; i < R[cur].size(); i++){
            int nxt = R[cur][i].first;
            int cst = R[cur][i].second;
            if((dist[nxt] + cst) == dist[cur]){
                cnt++;
                q.push(nxt);
            }
        }
    }
    printf("%d\n%d\n", dist[e], cnt);
    return 0;
}