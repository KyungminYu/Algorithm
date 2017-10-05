#include <stdio.h>
#include <vector>
using namespace std;

vector<int> G;
int chk[50], n;
void dfs(int v, int depth){
	chk[v] = 1;
	if(depth == 6){
		for(int i = 1; i <= n; i++){
			if(chk[i]) printf("%d ", G[i]);
		}
		printf("\n");
		chk[v] = 0;
		return;
	}

	for(int i = v + 1; i <= n; i++){
		if(chk[i]) continue;
		dfs(i, depth + 1);
	}

	chk[v] = 0;
}

int main(){
	while(1){
		scanf("%d", &n);
		if(n == 0) break;
		G.clear();
		G.resize(n + 1);
		for(int i = 1; i <= n; i++) scanf("%d", &G[i]);
		for(int i = 1; i <= n; i++) dfs(i, 1);
		printf("\n");
	}
	return 0;
}