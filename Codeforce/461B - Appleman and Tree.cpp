#include <stdio.h>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;
vector<int> G[100001];
long long dp[100001][2], p[100001];

void dfs(int v, int pre){
    dp[v][0] = 1 - p[v];
    dp[v][1] = p[v];
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(nxt == pre) continue;
        dfs(nxt, v);
        int tdp[2];
        tdp[0] = tdp[1] = 0;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(i == 0){
                    tdp[0] += (dp[v][i] * dp[nxt][j]) % MOD;
                    tdp[0] %= MOD;
                }
                if(i == 1 || j == 1){
                    tdp[1] += (dp[v][i] * dp[nxt][j]) % MOD;
                    tdp[1] %= MOD;
                }
            }
        }
        dp[v][1] = tdp[1];
        dp[v][0] = tdp[0];
    }
}
int main(){
    int n, t; scanf("%d", &n);
    for(int i = 1; i < n; i++){
        scanf("%d", &t);
        G[t].push_back(i);
    }
    for(int i = 0; i < n; i++) scanf("%d", &p[i]);
    dfs(0, -1);
    printf("%lld\n", dp[0][1]);

    return 0;
}