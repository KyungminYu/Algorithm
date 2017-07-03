#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<int> T[101];


int main(){
	int n, m, x, y, u, v;
	scanf("%d %d %d %d", &n, &x, &y, &m);
	for (int i = 0; i < m; i++){
		scanf("%d %d", &u, &v);
		T[u].push_back(v);
		T[v].push_back(u);
	}
	queue<pair<int, int> > q;
	q.push(make_pair(x, 0));
	int ans = -1;
	while (!q.empty()) {
		int cur = q.front().first;
		int depth = q.front().second;
		q.pop();
		if (cur == y){
			ans = depth;
			break;
		}
		for (int i = 0; i < T[cur].size(); i++){
			int nxt = T[cur][i];
			if (nxt == cur) continue;
			q.push(make_pair(nxt, depth + 1));
		}
	}
	printf("%d\n", ans);
	return 0;
}