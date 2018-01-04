#include <stdio.h>
#include <vector>
using namespace std;
const int NMAX = 501;
const int INF = 1e9;
vector<pair<int, int> > G[NMAX];
int dist[NMAX];
int n, m;
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, c; 
		scanf("%d %d %d", &a, &b, &c);
		G[a].push_back({b, c});
	}
	dist[1] = 0;
	for(int i = 2; i <= n; i++)
		dist[i] = INF;
	int negativeCycle = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int k = 0; k < G[j].size(); k++){
				int nxt = G[j][k].first;
				int cst = G[j][k].second;
				if(dist[j] != INF && dist[nxt] > dist[j] + cst){
					dist[nxt] = dist[j] + cst;
					if(i == n) negativeCycle = 1;
				}
			}
		}
	}
	if(negativeCycle) printf("-1");
	else{
		for(int i = 2; i <= n; i++)
			printf("%d\n", dist[i] == INF ? -1 : dist[i]);
	}

	return 0;
}