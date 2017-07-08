#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

vector<pair<int, int> > T[100001];
int MAX, mxind, chk[100001];
void dfs(int v, int depth){
    chk[v] = 1;
    if(MAX < depth) {
        MAX = depth;
        mxind = v;
    }
    for(int i = 0; i < T[v].size(); i++){
        int nxt = T[v][i].first;
        int dep = T[v][i].second;
        if(chk[nxt]) continue;
        dfs(nxt, depth + dep);
    }
}
int main(){
    int t, u, v, w;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++){
        scanf("%d", &u);
        while(scanf("%d", &v)){
            if(v == -1) break;
            scanf("%d", &w);
            T[v].push_back(make_pair(u, w));
            T[u].push_back(make_pair(v, w));
        }
    }
    MAX = mxind = 0;
    dfs(1, 0);
    MAX = 0;
    memset(chk, 0, sizeof(chk));
    dfs(mxind, 0);
    printf("%d\n", MAX);
    return 0;
}