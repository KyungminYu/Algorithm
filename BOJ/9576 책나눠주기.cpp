#pragma GCC optimize("O2")
#include <stdio.h>

const int MAXN = 1001;
int n, m;
int chk[MAXN], LR[MAXN][2], book[MAXN], stu[MAXN];
int dfs(int v){
    chk[v] = 1;
    for(int nxt = LR[v][0]; nxt <= LR[v][1]; nxt++){
        if(book[nxt] == -1 || !chk[book[nxt]] && dfs(book[nxt])){
            book[nxt] = v;
            stu[v] = nxt;
            return 1;
        }
    }
    return 0;
}
int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++)
            book[i] = -1;
        for(int i = 1; i <= m; i++){
            scanf("%d %d", &LR[i][0], &LR[i][1]);
            stu[i] = -1;
        } 
        int res = 0;
        for(int i = 1; i <= m; i++){
            if(stu[i] == -1){
                for(int j = 1; j <= m; j++) 
                    chk[j] = 0;
                if(dfs(i)) res++;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}