#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int NMAX = 1001;
vector<int> G[NMAX];
int indegree[NMAX], cost[NMAX], time[NMAX];
int main(){
    int T; scanf("%d", &T);
    while(T--){
        int n, k; scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &cost[i]);
            time[i] = 0;
            G[i].clear();
        }
        for(int i = 0; i < k; i++){
            int u, v; scanf("%d %d", &u, &v);
            G[u].push_back(v);
            indegree[v]++;
        }
        int w; scanf("%d", &w);
        
        queue<int> q;
        for(int i = 1; i <= n; i++){
            if(!indegree[i]) {
                q.push(i);
                time[i] = cost[i];    
            }
        }
        
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int nxt : G[cur]){
                time[nxt] = time[nxt] > time[cur] + cost[nxt]
                          ? time[nxt] : time[cur] + cost[nxt];
                if(!(--indegree[nxt])) q.push(nxt);
            }
        }
        printf("%d\n", time[w]);
    }
    
    return 0;
}