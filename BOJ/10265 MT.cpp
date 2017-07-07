#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

map<int, int> mp;
vector<int> G[1001], R[1001], scc[1001], MG[1001];
pair<int, int> SET[1001];
stack<int> postStack;
queue<int> q;
int chk[1001], rchk[1001], indegree[1001];
int dp[1001][1001];
int n, k, u;

void dfs(int v){
    chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(chk[nxt]) continue;
        dfs(nxt);
    }
    postStack.push(v);
}
void rdfs(int v, int ind){
    rchk[v] = 1;
    mp[v] = ind;
    scc[ind].push_back(v);
    for(int i = 0; i < R[v].size(); i++){
        int nxt = R[v][i];
        if(rchk[nxt]) continue;
        rdfs(nxt, ind);
    }
}
int sdfs(int v, int pre){
    int ret = 1;
    for(int i = 0; i < MG[v].size(); i++){
        int nxt = MG[v][i];
        if(nxt == pre) continue;
        ret += sdfs(nxt, v);
    }
    return ret;
}
int knapsack(int pos, int val, int n){
    if(pos > n) return 0;
    int &ret = dp[pos][val];
    if(ret != -1) return ret;
    ret = knapsack(pos + 1, val, n);
    if(val >= SET[pos].first){
        for(int i = SET[pos].first; i <= SET[pos].first + SET[pos].second; i++){
            if(i > val) break;
            ret = max(ret, knapsack(pos + 1, val - i, n) + i);
        }
    }
    return ret;
}
int main(){
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d", &u);
        G[i].push_back(u);
        R[u].push_back(i);
    }
    for(int i = 1; i <= n; i++){
        if(chk[i]) continue;
        dfs(i);
    }
    int sccInd = 0;
    while(!postStack.empty()){
        int cur = postStack.top();
        postStack.pop();
        if(rchk[cur]) continue;
        rdfs(cur, sccInd++);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < G[i].size(); j++){
            int nxt = G[i][j];
            if(mp[i] == mp[nxt]) continue;
            MG[mp[nxt]].push_back(mp[i]);
            indegree[mp[i]]++;
        }
    }
    for(int i = 0; i < sccInd; i++) if(indegree[i] == 0) q.push(i);
    
    int setInd = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        SET[setInd].first = scc[cur].size();
        SET[setInd].second = sdfs(cur, -1) - 1;
        setInd++;
    }

    memset(dp, -1, sizeof(dp));
    printf("%d\n", knapsack(0, k, setInd - 1));

    return 0;
}