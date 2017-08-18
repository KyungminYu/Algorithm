#include <stdio.h>
int dp[101];
int main(){
    int T; scanf("%d", &T);
    for(int i = 2; i <= 100; i++){
        for(int j = 1; j <= 100; j++){
            if(j % i) continue;
            dp[j] ^= 1;
        }
    }
    while(T-- > 0){
        int n, res = 0; scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            if(dp[i]) continue;
            res++; 
        }
        printf("%d\n", res);
    }
    return 0;
}