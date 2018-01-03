#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
	int n, m, cnt = 0;
	cin >> n >> m;
	queue<int> q;
	vector<int> res;
	for (int i = 1; i <= n; i++)
		q.push(i);
	while (!q.empty()) {
		int val = q.front();
		q.pop();
		cnt++;
		if (cnt == m) res.push_back(val); 
		else q.push(val);

		cnt %= m;
	}
	cout << "<";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
		if(i < res.size() - 1) cout << ", ";
	}
	cout << ">";
	return 0; 
}