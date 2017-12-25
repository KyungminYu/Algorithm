#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int NMAX = 10001;
vector<int> G[NMAX];
stack<int> stk;
int num[NMAX], finished[NMAX];
vector<vector<int> > SCC;
int n, m, SN, timer;
int dfs(int v){
	stk.push(v);
	num[v] = ++timer;

	int res = num[v];
	for(int i = 0; i < G[v].size(); i++){
		int nxt = G[v][i];
		if(!num[nxt]) 
			res = min(res, dfs(nxt));
		if(!finished[nxt]) 
			res = min(res, num[nxt]);
	}

	if(res == num[v]){
		vector<int> cSCC;
		while(1){
			int tmp = stk.top();
			stk.pop();
			cSCC.push_back(tmp);
			finished[tmp] = 1;
			if(tmp == v) break;
		}
		sort(cSCC.begin(), cSCC.end());
		SCC.push_back(cSCC);
		SN++;
	}
	return res;
}
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v; 
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
	}
	
	for(int i = 1; i <= n; i++){
		if(num[i]) continue;
		dfs(i);
	}
	sort(SCC.begin(), SCC.end());
	printf("%d\n", SN);
	for(int i = 0; i < SN; i++){
		for(int j = 0; j < SCC[i].size(); j++)
			printf("%d ", SCC[i][j]);
		printf("-1\n");
	}


	return 0;
}