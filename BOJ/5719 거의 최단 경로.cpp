#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;
const int NMAX = 505;
int G[NMAX][NMAX];
int n, m, s, d;
int dist[NMAX];
void dijkstra(){
	for(int i = 0; i < n; i++) 
		dist[i] = INF;
	dist[s] = 0;

	priority_queue<pair<int, int> > pq;
	pq.push({0, s});

	while(!pq.empty()){
		int here = pq.top().second;
		pq.pop();
		for(int i = 0; i < n; i++){
			if(G[here][i] != -1 && dist[here] + G[here][i] < dist[i]){
				dist[i] = dist[here] + G[here][i];
				pq.push({-dist[i], i});
			}
		}
	}

}
void erase(){
	queue<int> q;
	q.push(d);
	while(!q.empty()){
		int here = q.front();
		q.pop();
		for(int i = 0; i < n; i++){
			if(G[i][here] != -1 && dist[here] == dist[i] + G[i][here]){
				G[i][here] = -1;
				q.push(i);
			}
		}
	}
}
int main(){
	while(1){
		scanf("%d %d", &n, &m);
		if(n == 0 && m == 0) break;
		scanf("%d %d", &s, &d);
		memset(G, -1, sizeof(G));
		for(int i = 0; i < m; i++){
			int u, v, w; scanf("%d %d %d", &u, &v, &w);
			G[u][v] = w;
		}
		dijkstra();
		erase();
		dijkstra();
		if(dist[d] == 1e9) dist[d] = -1;
		printf("%d\n", dist[d]);
	}
	return 0;
}