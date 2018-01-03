#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
	int n; cin >> n;
	deque<int> dq;
	while (n--) {
		string in; cin >> in;
		if (in == "push_front") {
			int x; cin >> x;
			dq.push_front(x);
		}
		else if (in == "push_back") {
			int x; cin >> x;
			dq.push_back(x);
		}
		else if (in == "pop_front") {
			if (dq.empty()) cout << "-1\n";
			else {
				cout << dq.front() << "\n";
				dq.pop_front();
			}
		}
		else if (in == "pop_back") {
			if (dq.empty()) cout << "-1\n";
			else {
				cout << dq.back() << "\n";
				dq.pop_back();
			}
		}
		else if (in == "size") cout << dq.size() << "\n";
		else if (in == "empty") cout << dq.empty() << "\n";
		else if (in == "front") {
			if (dq.empty()) cout << "-1\n";
			else cout << dq.front() << "\n";
		}
		else if (in == "back") {
			if (dq.empty()) cout << "-1\n";
			else cout << dq.back() << "\n";
		}
	}
	return 0;
}