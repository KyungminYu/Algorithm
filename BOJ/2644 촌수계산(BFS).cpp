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

	//x부터 y까지 BFS를 사용한다.
	//큐에는 노드 번호와 그 노드의 깊이를 쌍으로 집어넣는다.
	queue<pair<int, int> > q;
	//x부터 BFS시작
	q.push(make_pair(x, 0));
	int ans = -1;
	while (!q.empty()) {
		int cur = q.front().first;
		int depth = q.front().second;
		q.pop();
		//y를 찾으면 ans에 depth를 할당하고 끝낸다
		if (cur == y){
			ans = depth;
			break;
		}
		for (int i = 0; i < T[cur].size(); i++){
			int nxt = T[cur][i];
			if (nxt == cur) continue;
			//자식 노드의 깊이는 부모 노드의 깊이에 1을 더해서 할당한다.
			q.push(make_pair(nxt, depth + 1));
		}
	}
	printf("%d\n", ans);
	return 0;
}