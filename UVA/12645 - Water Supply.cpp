#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
vector<int> G[1001], post;
int chk[1001];
void dfs(int v, int flag){
    chk[v] = 1;
    for(int i = 0; i < G[v].size(); i++){
        if(chk[G[v][i]]) continue;
        dfs(G[v][i], flag);
    }
    if(flag) post.push_back(v);
}
int main(){
    int N, M, u, v, cnt;
    while(scanf("%d %d", &N, &M) != EOF){
        for(int i = 0; i <= N; i++) G[i].clear();
        post.clear();
        memset(chk, 0, sizeof(chk));
        for(int i = 0; i < M ; i++){
            scanf("%d %d", &u, &v);
            if(v == 0) continue;
            G[u].push_back(v);
        }   
        for(int i = 0; i <= N; i++){
            if(chk[i]) continue;
            dfs(i, 1);
        }
        memset(chk, 0, sizeof(chk));
        cnt = -1;
        for(int i = post.size() - 1; i >= 0; i--){
            if(chk[post[i]]) continue;
            dfs(post[i], 0);
            cnt++;
        }
        printf("%d\n", cnt);
    }

    return 0;
}