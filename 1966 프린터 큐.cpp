#include <iostream>
#include <queue>
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		queue<pair<int, int> > q;
		priority_queue<int> pq;
		for (int i = 0; i < n; i++) {
			int priority; cin >> priority;
			q.push({i, priority });
			pq.push(priority);
		}
		int res = 0;
		while (!q.empty()) {
			int idx = q.front().first;
			int pri = q.front().second;
			q.pop();
			if (pq.top() == pri) {
				res++;
				pq.pop();
				if (idx == m) break;
			}
			else {
				q.push({idx, pri});
			}
		}
		cout << res << "\n";
	}

	return 0;
}