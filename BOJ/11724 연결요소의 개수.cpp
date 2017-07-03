#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G[1001];
int chk[1001];

void dfs(int v){
	chk[v] = 1;
	for(int i = 0; i < G[v].size(); i++){
		int nxt = G[v][i];
		if(chk[nxt]) continue;
		dfs(nxt);
	}
}
int main(){
	int n, m, u, v;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	//DFS를 이용해서 CC를 찾는다.
	int ans = 0;
	for(int i = 1; i <= n; i++){
		if(chk[i]) continue;
		ans++;
		dfs(i);
	}

	printf("%d\n", ans);
	return 0;
}