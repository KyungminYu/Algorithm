#include <stdio.h>
#include <queue>
using namespace std;

#define INF 1e9
int Map[102][102];
int dist[102][102];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			scanf("%1d", &Map[i][j]);
			dist[i][j] = INF;
		}
	}

	priority_queue<pair<int, pair<int, int> > > pq;
	dist[1][1] = 1;
	pq.push(make_pair(-dist[1][1], make_pair(1, 1)));
	while (!pq.empty()) {
		int x = pq.top().second.first;
		int y = pq.top().second.second;
		int cost = pq.top().first * (-1);
		pq.pop();
		for (int i = 0; i < 4; i++) {
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (Map[tx][ty] == 1 && dist[tx][ty] > cost + 1) {
				dist[tx][ty] = cost + 1;
				pq.push(make_pair(dist[tx][ty] * (-1), make_pair(tx, ty)));
			}
		}
	}
	printf("%d\n", dist[N][M]);
	return 0;
}