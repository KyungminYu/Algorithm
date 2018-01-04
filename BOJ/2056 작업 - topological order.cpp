#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int NMAX = 10005;
int time[NMAX], spend[NMAX], indegree[NMAX];
vector<int> G[NMAX], R[NMAX];

int main(){
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int m; scanf("%d %d", &time[i], &m);
		for(int j = 0; j < m; j++){
			int u; scanf("%d", &u);
			G[i].push_back(u);
			R[u].push_back(i);
			indegree[u]++;
		}
	}

	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(!indegree[i]) q.push(i);
	}
	
	int res = 0;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		int mx = 0;
		for(int nxt : R[cur])
			mx = max(mx, spend[nxt]);
		spend[cur] = mx + time[cur];
		res = max(res, spend[cur]);
		for(int nxt : G[cur]){
			if(!(--indegree[nxt])) 
				q.push(nxt);
		}
	}
	printf("%d\n", res);
	return 0;
}