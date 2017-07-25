#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> ans;
vector<int> G[10000];
int chk[10000], cnt[10000];
int mmax;
int dfs(int v){
    int ret = 0; chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(chk[nxt]) continue;
        ret += dfs(nxt); 
    }
    return ret + 1;
}
int main(){ 
    int n, m; scanf(" %d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;scanf(" %d %d", &u, &v);
        G[v - 1].push_back(u - 1);
    }
    mmax = -1;
    for(int i = 0; i < n; i++){
        memset(chk, 0, sizeof(chk));
        cnt[i] = dfs(i);
        mmax = mmax < cnt[i] ? cnt[i] : mmax;
    }
    for(int i = 0; i < n; i++)
        if(cnt[i] == mmax) ans.push_back(i + 1);
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
    return 0;
}