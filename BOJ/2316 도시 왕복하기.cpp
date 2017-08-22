#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MAXN = 400;
const int MAXV = MAXN * 2 + 2;
int flow[MAXV][MAXV], capacity[MAXV][MAXV];
vector<int> G[MAXV];
void addEdge(int u, int v, int w){
    capacity[u][v] += w;
    G[u].push_back(v);
    G[v].push_back(u);
}
int main(){
    int n, p; scanf("%d %d", &n, &p);
    for(int i = 1; i <= n; i++)
        addEdge(i, i + MAXN, 1);
    for(int i = 0; i < p; i++){
        int u, v; scanf("%d %d", &u, &v);
        addEdge(u + MAXN, v, 1);
        addEdge(v + MAXN, u, 1);
    }
    int total = 0, source = MAXN + 1, sink = 2;
    while(1){
        int prev[MAXV];
        for(int i = 1; i <= n; i++) prev[i] = prev[i + MAXN] = -1;
        queue<int> q;
        q.push(source);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < G[cur].size(); i++){
                int nxt = G[cur][i];
                if(capacity[cur][nxt] - flow[cur][nxt] > 0 && prev[nxt] == -1){
                    prev[nxt] = cur;
                    q.push(nxt);
                    if(nxt == sink) break;
                }
            }
        }
        if(prev[sink] == -1) break;
        for(int i = sink; i != source; i = prev[i]){
            flow[prev[i]][i]++;
            flow[i][prev[i]]--;
        }
        total++;
    }
    printf("%d\n", total);
    return 0;
}