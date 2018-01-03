#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	int n; cin >> n;
	int res = 0;
	while (n--) {
		stack<char> stk;
		string in; cin >> in;
		int len = in.size();
		for (int i = 0; i < len; i++) {
			if (stk.empty()) stk.push(in[i]);
			else {
				if (stk.top() == in[i]) stk.pop();
				else stk.push(in[i]);
			}
		}
		if (stk.empty()) res++;
	}
	cout << res;
	return 0;
}