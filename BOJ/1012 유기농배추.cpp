#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

int Map[52][52];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0 };
void bfs(int x, int y){
	queue<pair<int, int> > q;
	q.push(make_pair(x, y));
	Map[x][y] = 0;
	while (!q.empty()){
		int rx = q.front().first;
		int ry = q.front().second;
		Map[rx][ry] = 0;
		q.pop();
		for (int i = 0; i < 4; i++){
			int tx = rx + dx[i];
			int ty = ry + dy[i];
			if (Map[tx][ty] == 1){
				q.push(make_pair(tx, ty));
				Map[tx][ty] = 0;
			}
		}
	}
}
int main(){
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++){
		int M, N, K, X, Y, cnt = 0;
		scanf("%d %d %d", &M, &N, &K);
		memset(Map, 0, sizeof(Map));
		for (int j = 0; j < K; j++){
			scanf("%d %d", &X, &Y);
			Map[X + 1][Y + 1] = 1;
		}
		for (int i = 1; i <= M; i++){
			for (int j = 1; j <= N; j++){
				if (Map[i][j] == 1){
					bfs(i, j);
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}