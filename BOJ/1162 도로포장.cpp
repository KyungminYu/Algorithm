#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

const int NMAX = 10001;
const int KMAX = 21;
const int INF = 0x3f3f3f3f;

struct edge{
	int v, cost, cover;
	edge(){}
	edge(int v, int cost){
		this->v = v;
		this->cost = cost;
	}
	edge(int v, int cost, int cover){
		this->v = v;
		this->cost = cost;
		this->cover = cover;
	}
	int operator < (edge e) const{
		return cost > e.cost;
	}
};

int n, m, k, res = INF;
int dist[NMAX][KMAX];
vector<edge> G[NMAX];

void dijkstra(int s){
	memset(dist, INF, sizeof(dist));
    dist[s][k] = 0;
    priority_queue<edge> pq;
    pq.push({s, 0, k});
    while(!pq.empty()){
        int here=pq.top().v;
        int cost=pq.top().cost;
        int cover=pq.top().cover;
        pq.pop();
        if(dist[here][cover] < cost) continue;
        for(auto node: G[here]){
            int ncst = node.cost;
            int next = node.v;
            if(dist[next][cover] > cost + ncst){
                dist[next][cover] = cost + ncst;
                pq.push({next, dist[next][cover], cover});
            }
            if(cover){
            	if(dist[next][cover - 1] > cost){
            		dist[next][cover - 1] = cost;
                	pq.push({next, dist[next][cover - 1], cover - 1});

            	}
            }
        }        
    }
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < m; i++){
		int u, v, c; scanf("%d %d %d", &u, &v, &c);
		G[u].push_back({v, c});
		G[v].push_back({u, c});
	}
	dijkstra(1);
	for(int i = 0; i <= k; i++)
		res = dist[n][i] < res ? dist[n][i] : res;
	printf("%d\n", res);

	return 0;
}