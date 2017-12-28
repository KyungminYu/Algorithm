#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int NMAX = 100001;
vector<int> G[NMAX];
stack<int> stk;
int num[NMAX], fin[NMAX], SCCNum[NMAX], indegree[NMAX];
int n, m, SN, timer;
int dfs(int v){
	stk.push(v);
	num[v] = ++timer;

	int res = num[v];
	for(int i = 0; i < G[v].size(); i++){
		int nxt = G[v][i];
		if(!num[nxt]) 
			res = min(res, dfs(nxt));
		if(!fin[nxt]) 
			res = min(res, num[nxt]);
	}

	if(res == num[v]){
		while(1){
			int tmp = stk.top();
			stk.pop();
			fin[tmp] = 1;
			SCCNum[tmp] = SN;
			if(tmp == v) break;
		}
		SN++;
	}
	return res;
}
int main(){
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &m);
		timer = SN = 0;
		memset(num, 0, sizeof(num));
		memset(fin, 0, sizeof(fin));
		memset(SCCNum, 0, sizeof(SCCNum));
		memset(indegree, 0, sizeof(indegree));
		for(int i = 1; i <= n; i++) 
			G[i].clear();
		for(int i = 0; i < m; i++){
			int u, v; 
			scanf("%d %d", &u, &v);
			G[u].push_back(v);
		}
		
		for(int i = 1; i <= n; i++){
			if(num[i]) continue;
			dfs(i);
		}
		for(int u = 1; u <= n; u++){
			for(int j = 0; j < G[u].size(); j++){
				int v = G[u][j]; 
				indegree[SCCNum[v]] 
					+= (SCCNum[u] != SCCNum[v]);
			}
		}
		int res = 0;
		for(int i = 0; i < SN; i++)
			res += (indegree[i] == 0);
		printf("%d\n", res);
	}
	return 0;
}