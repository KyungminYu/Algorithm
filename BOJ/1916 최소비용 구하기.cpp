#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define INF 1e9

vector<pair<int, int> > G[1001];
int dist[1001];
int main(){
	int N, M;
	int u, v, w, s, e;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
	}
	scanf("%d %d", &s, &e);

	for (int i = 0; i <= N; i++)
		dist[i] = INF;

	dist[s] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, s));

	while (!pq.empty()) {
		int cur = pq.top().second;
		int cost = pq.top().first * (-1);
		pq.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			if (dist[G[cur][i].first] > cost + G[cur][i].second) {
				dist[G[cur][i].first] = cost + G[cur][i].second;
				pq.push(make_pair(dist[G[cur][i].first] * (-1), G[cur][i].first));
			}
		}
	}
	printf("%d\n", dist[e]);
	return 0;
}