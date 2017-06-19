#include <stdio.h>
#include <vector>
using namespace std;

int G[101][101];
int visit[101][101];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int N, M, K, u, v, mass, MAX;
void dfs(int x, int y){
	visit[x][y] = 1;
	mass++;
	for (int i = 0; i < 4; i++){
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (visit[tx][ty] == 0 && G[tx][ty] == 1 && 1 <= tx && tx <= N && 1 <= ty && ty <= M)
			dfs(tx, ty);
	}
}
int main(){
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++){
		scanf("%d %d", &u, &v);
		G[u][v] = 1;
	}
	MAX = -1;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			if (visit[i][j] == 0 && G[i][j] == 1){
				mass = 0;
				dfs(i, j);
				if (MAX < mass) MAX = mass;
			}
		}
	}
	printf("%d\n", MAX);
	return 0;
}