#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int parent[10001];
priority_queue<pair<int, pair<int, int> > > pq;
int find(int v){
	if(v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
int main(){
	int V, E, u, v, w, cnt, ans;
	scanf("%d %d", &V, &E);
	for(int i = 0 ; i < E; i++){
		scanf("%d %d %d", &u, &v, &w);
		pq.push(make_pair(-w, make_pair(u, v)));
	}
	for(int i = 1; i <= V; i++) parent[i] = i;
	ans = cnt = 0;
	while(cnt < V-1){
		int p1 = find(pq.top().second.first);
		int p2 = find(pq.top().second.second);
		if(p1 != p2) {
			parent[p2] = p1;
			ans+=(-pq.top().first);
			cnt++;
		}
		pq.pop();
	}
	printf("%d\n", ans);
	return 0;
}