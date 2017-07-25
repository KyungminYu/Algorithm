#include <stdio.h>
int mp[1001];
int dp[1001];
int main(){
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &mp[i]);
        dp[i] = 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            if(mp[i] > mp[j] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
    }
    int mx = -1;
    for(int i = 1; i <= n; i++){
        if (mx < dp[i]) mx = dp[i];
    }
    printf("%d\n", mx);
    return 0;
}