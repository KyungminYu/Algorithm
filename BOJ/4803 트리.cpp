#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G[501];
int chk[501];
int flag;
void dfs(int v, int par){
    chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(nxt == par) continue;
        if(chk[nxt]) {
            flag = 0;
            continue;
        }
        dfs(nxt, v);
    }
}
int main(){
    int n, m, T = 1;
    while(scanf("%d %d", &n, &m)){
        int u, v, ans = 0;
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; i++) {
            G[i].clear();
            chk[i] = 0;
        }
        for(int i = 0; i < m; i++){
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i = 1; i <= n; i++){
            if(chk[i]) continue;
            flag = 1;
            dfs(i, -1);
            if(flag) ans++;
        }
        if(ans == 0) printf("Case %d: No trees.\n", T++);
        else if(ans == 1) printf("Case %d: There is one tree.\n", T++);
        else if(ans > 1) printf("Case %d: A forest of %d trees.\n", T++, ans);
    }
    return 0;
}