#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int NMAX = 1001;
vector<int> G[NMAX];
int indegree[NMAX], res[NMAX];

int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int t; scanf("%d", &t);
        if(t == 0) continue;
        int a; scanf("%d", &a);
        for(int j = 1; j < t; j++){
            int b; scanf("%d", &b);
            G[a].push_back(b);
            indegree[b]++;
            a = b;
        }
    }
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!indegree[i])
            q.push(i);
    }
    if(q.empty()){
        printf("0");
        return 0;
    }
    for(int i = 0; i < n; i++){
        if(q.empty()){
            printf("0");
            return 0;
        }
        int cur = q.front();
        q.pop();
        res[i] = cur;
        for(int nxt : G[cur]){
            if(!(--indegree[nxt]))
                q.push(nxt);
        }
    }
    for(int i = 0; i < n; i++)
        printf("%d\n", res[i]);
    return 0;
}