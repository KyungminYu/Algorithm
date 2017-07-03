#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G[101];
int visit[101];
int post[101];
int cnt = 0;
void dfs(int v, int d){
	visit[v] = 1;
	post[v] = cnt++;
	for (int i = 0; i < G[v].size(); i++){
		if (visit[G[v][i]] == 0)
			dfs(G[v][i], d);
	}
	cnt--;
}
int main(){
	int n, s, e, m, x, y;
	scanf("%d", &n);
	scanf("%d %d", &s ,&e);
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(s, e); 
	visit[e] == 0 ? printf("-1\n") : printf("%d\n", post[e]);
	return 0;
}