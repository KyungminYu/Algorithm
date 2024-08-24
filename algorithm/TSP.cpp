#include <stdio.h>

#define INF 2e8
#define MAX_N 16

int n; 
int w[MAX_N][MAX_N];
int dp[MAX_N][1 << MAX_N];

int tsp(int depth, int from, int visit) {
    if (n <= depth) {
        return w[from][0] == 0 ? INF : w[from][0];
    }
    if (dp[from][visit] != 0) {
        return dp[from][visit];
    }
    dp[from][visit] = INF;
    for (int to = 0; to < n; ++to){
        if (visit & (1 << to) || w[from][to] == 0) continue;
        int dist = tsp(depth + 1, to, visit | (1 << to)) + w[from][to];
        if (dist < dp[from][visit]) {
            dp[from][visit] = dist;
        } 
    }
    return dp[from][visit];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d ", &w[i][j]);
        }
    }     
    bool visit[MAX_N] = {false,};  
    visit[0] = true; 
    printf("%d\n", tsp(1, 0, 1));
    return 0;
}