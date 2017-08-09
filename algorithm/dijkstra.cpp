#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define INF 1e9
#define SIZE 300001

vector<pair<int, int> > edges[SIZE];
void dijkstra(int V, int K){
	vector<int> dist(V + 1, INF);

	dist[K] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, K));
	while (!pq.empty()) {
		int current = pq.top().second;
		int currentcost = pq.top().first * -1;
		pq.pop();
		if (currentcost <= dist[current]) {
			for (int i = 0; i < edges[current].size(); i++) {
				int next = edges[current][i].first;
				int cost = edges[current][i].second;
				if (currentcost + cost < dist[next]) {
					dist[next] = currentcost + cost;
					pq.push(make_pair(dist[next] * -1, next));
				}
			}
		}
	}

	for (int i = 1; i <= V; i++){
		if (dist[i] == INF)
			printf("INF\n");
		else
			printf("%d\n", dist[i]);
	}
}
int main(){
	int V, E, K;
	int u, v, w;
	scanf("%d %d", &V, &E);
	scanf("%d", &K);
	for (int i = 0; i < E; i++){
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back(make_pair(v, w));
	}
	dijkstra(V, K);
	return 0;
}