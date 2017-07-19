#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G[40001];
vector<int> ans; 
int chk[40001];
void dfs(int v){
    chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(chk[nxt]) continue;
        dfs(nxt);
    }
}
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        int c; scanf("%d", &c);
        while(c-- > 0){
            int l; scanf("%d", &l);
            G[i].push_back(n + l);
            G[n + l].push_back(i);
        }
    }
    for(int i = 1; i <= n; i++){
        if(chk[i]) continue;
        dfs(i);
        ans.push_back(i);
    }
    printf("%d\n", ans.size() - 1);
    for(int i = 1; i < ans.size(); i++)
        printf("%d %d\n", G[ans[0]][0] - n, ans[i]);
    return 0;
}