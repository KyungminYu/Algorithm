#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
	int n; cin >> n;
	queue<int> q;
	while (n--) {
		string in; cin >> in;
		if (in == "push") {
			int x; cin >> x;
			q.push(x);
		}
		else if (in == "pop") {
			if (q.empty()) cout << "-1\n";
			else {
				cout << q.front() << "\n";
				q.pop();
			}
		}
		else if (in == "size") cout << q.size() << "\n";
		else if (in == "empty") cout << q.empty() << "\n";
		else if (in == "front") {
			if (q.empty()) cout << "-1\n";
			else cout << q.front() << "\n";
		}
		else if (in == "back") {
			if (q.empty()) cout << "-1\n";
			else cout << q.back() << "\n";
		}
	}


	return 0;
}