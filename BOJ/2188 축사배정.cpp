#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int MAXN = 200;
const int MMAX = 2 * MAXN+ 2;
int flow[MMAX][MMAX], capacity[MMAX][MMAX]; 
vector<int> G[MMAX];

int main(){
    int total = 0;
    int source = 0, sink = MMAX - 1;
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        int s; scanf("%d", &s);
        for(int j = 0; j < s; j++){
            int u; scanf("%d", &u);
            capacity[i][u + MAXN] = 1;
            G[i].push_back(u + MAXN);
            G[u + MAXN].push_back(i);
        }
        capacity[source][i] = 1;
        G[source].push_back(i);
        G[i].push_back(source);
    }
    for(int i = 1; i <= m; i++) {
        capacity[i + MAXN][sink] = 1;
        G[i + MAXN].push_back(sink);
        G[sink].push_back(i + MAXN);
    }
    while(1){
        int prev[MMAX];
        memset(prev, -1, sizeof(prev));
        queue<int> q;
        q.push(source);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < G[cur].size(); i++){
                int nxt = G[cur][i];
                if(capacity[cur][nxt] - flow[cur][nxt] > 0 
                    && prev[nxt] == -1){
                    q.push(nxt);
                    prev[nxt] = cur;
                    if(nxt == sink) break;
                }
            }
        }
        if(prev[sink] == -1) break;
        for(int i = sink; i != source; i = prev[i]){
            flow[prev[i]][i]++;
            flow[i][prev[i]]--;
        }
        total ++;
    }
    printf("%d\n", total);
    return 0;
}