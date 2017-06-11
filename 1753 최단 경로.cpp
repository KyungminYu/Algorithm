#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

#define INF 3000000
vector<pair<int, int> >G[200001];
int dist[200001];
int main(){
	int V, E, K, u, v, w;
	scanf("%d %d %d", &V, &E, &K);
	for (int i = 0; i<E; i++){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
	}

	for (int i = 1; i <= V; i++) dist[i] = INF;
	priority_queue<pair<int, int> > pq;
	dist[K] = 0;
	pq.push(make_pair(0, K));

	while (!pq.empty()){
		int cur = pq.top().second;
		pq.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			int next = G[cur][i].first;
			int nextCost = G[cur][i].second;
			if (dist[cur] + nextCost < dist[next]) {
				dist[next] = dist[cur] + nextCost;
				pq.push(make_pair(-dist[next], next));
			}
		}
	}
	for (int i = 1; i <= V; i++){
		if (dist[i] == INF)
			printf("INF\n");
		else
			printf("%d\n", dist[i]);
	}
	return 0;
}