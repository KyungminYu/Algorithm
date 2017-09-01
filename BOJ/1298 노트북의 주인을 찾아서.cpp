#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

vector<int> G[101];
int A[101], B[101], chk[101];
int n, m;
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
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int a, b; scanf("%d %d", &a, &b);
		G[a].push_back(b);
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
	printf("%d\n", res);
	return 0;
}