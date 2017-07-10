#include <stdio.h>
#include <string.h>
using namespace std;
int G[1001], chk[1001];
void trav(int v){
    chk[v] = 1;
    if(!chk[G[v]]) trav(G[v]);
}
int main(){ 
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, ans = 0; scanf("%d", &n);
        memset(chk, 0, sizeof(chk));
        for(int i = 1; i <= n; i++) scanf("%d", &G[i]);
        for(int i = 1; i <= n; i++){
            if(chk[i]) continue;
            trav(i);
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}