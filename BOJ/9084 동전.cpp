#include <stdio.h>
#include <string.h>
int dp[10001], coin[21];
int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m; scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &coin[i]);
        scanf("%d", &m);
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; i++){
            dp[coin[i]]++;
            for(int j = 0; j <= m; j++){
                if(j - coin[i] < 0) continue;
                dp[j] += dp[j - coin[i]];
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}