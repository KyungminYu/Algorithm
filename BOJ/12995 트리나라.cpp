#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const long long MOD = 1000000007LL;
vector<int> tree[51];
int chk[51];
int size[51];
long long dp[51][51];
long long tdp[51];
long long ans;
void dfs(int v, int pre){
    dp[v][1] = 1;
    for(int i = 0; i < tree[v].size(); i++){
        int nxt = tree[v][i];
        if(nxt == pre) continue;
        dfs(nxt, v);
        memset(tdp, 0, sizeof(tdp));
        for(int i = 1; i <= size[v]; i++){
            for(int j = 1; j <= size[nxt]; j++){
                tdp[i + j] += dp[v][i] * dp[nxt][j];
                tdp[i + j] %= MOD;
            }
        } 
        size[v] += size[nxt];
        for(int i = 1; i <= size[v]; i++) {
            dp[v][i] += tdp[i];
            dp[v][i] %= MOD;
        }
    }
}
int main(){
    int n, k, u, v;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n - 1; i++){
        scanf("%d %d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) size[i] = 1;
    dfs(1, -1);
    for(int i = 1; i <= n; i++){
        ans += dp[i][k];
        ans %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}