#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int NMAX = 501;
vector<int> G[NMAX];
int indegree[NMAX], cost[NMAX], timer[NMAX];

int main(){
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &cost[i]);
        while(1){
            int p; scanf("%d", &p);
            if(p == -1) break;
            G[p].push_back(i);
            indegree[i]++;
        }
    }
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!indegree[i]){
            q.push(i);
            timer[i] = cost[i];
        } 
    }
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int nxt : G[cur]){
            timer[nxt] = timer[nxt] > timer[cur] + cost[nxt] 
                       ? timer[nxt] : timer[cur] + cost[nxt];
            if(!(--indegree[nxt]))
                q.push(nxt);
        }
    }
    
    for(int i = 1; i <= n; i++)
        printf("%d\n", timer[i]);
    return 0;
}