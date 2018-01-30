#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int n, indegree[11], indeg[11], pos[11], res[11];
vector<int> G[11];
char in[11];
int init(){
	for(int i = 0; i <= n; i++) {
		indeg[i] = indegree[i];
		pos[i] = 0;
	}
}
void solve(int flag, int base){
	priority_queue<int> pq;
	for(int i = 0; i <= n; i++){
		if(indeg[i] == 0) pq.push(flag * i);
	}
	for(int i = 0; i <= n; i++){
		int cur = flag * pq.top();
		pos[i] = cur;
		pq.pop();
		for(int nxt : G[cur]){
			if(--indeg[nxt] == 0)
				pq.push(flag * nxt);
		}
	}
	for(int i = 0; i <= n; i++)
		res[pos[i]] = base--;
	for(int i = 0; i <= n; i++)
		printf("%d", res[i]);
	printf("\n");
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		char c; scanf(" %c", &c);
		if(c == '<'){
			G[i + 1].push_back(i);
			indegree[i]++;
		}
		else{
			G[i].push_back(i + 1);
			indegree[i + 1]++;
		}
	}
	init();
	solve(-1, 9);
	init();
	solve(1, n);
	return 0;
}