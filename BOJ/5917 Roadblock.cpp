#pragma GCC optimize("O2")
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int origin[101][101], adj[101][101], dummy[101][101];
int path[101][101];
int n, m; 
void Floyd(int mat[101][101]){
     for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
            	if(mat[i][k] + mat[k][j] < mat[i][j]){
            		path[i][j] = k;
                	mat[i][j] = mat[i][k] + mat[k][j];
            	}
            }
        }
    }
}

int doublingLen(int s, int e, int len){
	if(path[s][e] != -1){
		int k = path[s][e];
		len = max(len, doublingLen(s, k, len));
		len = max(len, doublingLen(k, e, len));
		return len;
	}
	else{
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				dummy[i][j] = INF;
				if(i == j) dummy[i][j] = 0;
				dummy[i][j] = origin[i][j];
			}
		}
		dummy[s][e] *= 2;
		Floyd(dummy);
		return dummy[1][n];
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			origin[i][j] = adj[i][j] = INF;
			if(i == j) origin[i][j] = adj[i][j] = 0;
		}
	}
	for(int i = 0; i < m; i++){
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		origin[u][v] = origin[v][u] = w;
		adj[u][v] = adj[v][u] = w;
	}

	memset(path, -1, sizeof(path));
	Floyd(adj);
	int originLen = adj[1][n];
	printf("%d\n", doublingLen(1, n, originLen) - originLen);
	return 0;
}