#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<int> G[32001];
int indegree[32001];
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int a, b; scanf("%d %d", &a, &b);
        G[a].push_back(b);
        indegree[b]++;
    }
    
    priority_queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!indegree[i]) q.push(-i);
    }
    
    while(!q.empty()){
        int cur = -q.top();
        q.pop();
        printf("%d ", cur);
        for(int nxt : G[cur]){
            if(!(--indegree[nxt]))
                q.push(-nxt);
        }
    }
    
    return 0;
}