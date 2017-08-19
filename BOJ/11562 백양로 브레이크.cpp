#include <stdio.h>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int dist[251][251];
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    for(int i = 0; i < m; i++){
        int u, v, b; scanf("%d %d %d", &u, &v, &b);
        if(b) dist[u][v] = dist[v][u] = 0;
        else{
            dist[u][v] = 0;
            dist[v][u] = 1;
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); 
        }
    }
    int q; scanf("%d", &q);
    for(int i = 0; i< q; i++){
        int u, v; scanf("%d %d", &u, &v);
        printf("%d\n", dist[u][v]);
    }
    return 0;
}