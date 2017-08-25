#pragma GCC optimize("O2")
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
const int MAXN = 1001;
int A[MAXN], B[MAXN], chk[MAXN];
vector<int> G[MAXN];
int dfs(int v){
	chk[v] = 1;
	for(int i = 0; i < G[v].size(); i++){
		int nxt = G[v][i];
		if(B[nxt] == -1 || !chk[B[nxt]] && dfs(B[nxt])){
			A[v] = nxt;
			B[nxt] = v;
			return 1;
		}
	}
	return 0;
}
int main(){
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		int s; scanf("%d", &s);
		for(int j = 1; j <= s; j++){
			int u; scanf("%d", &u);
			G[i].push_back(u);
		}
	}
	int res = 0;
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	for(int i = 1; i <= n; i++){
		if(A[i] == -1){
			memset(chk, 0, sizeof(chk));
			if(dfs(i)) res++;
		}
	}
	printf("%d", res);
	return 0;
}