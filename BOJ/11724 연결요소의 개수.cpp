#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G[1001];
int visit[1001];
void dfs(int v){
	visit[v] = 1;
	for (int i = 0; i < G[v].size(); i++){
		if (visit[G[v][i]] == 0) 
			dfs(G[v][i]);
	}
}
int main(){
	int N, M, u, v, cnt = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= N; i++){
		if (visit[i] == 0) {
			dfs(i);
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}