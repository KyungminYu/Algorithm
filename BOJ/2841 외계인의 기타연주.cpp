#include <iostream>
#include <stack>
using namespace std;

stack<int> stk[7];
int main() {
	int N, P, move = 0;
	cin >> N >> P;
	while (N--) {
		int lnum, pnum;
		cin >> lnum >> pnum;
		while (!stk[lnum].empty() && stk[lnum].top() > pnum) {
			stk[lnum].pop();
			move++;
		}
		if (stk[lnum].empty() || stk[lnum].top() != pnum) {
			stk[lnum].push(pnum);
			move++;
		}
	}
	cout << move << "\n";
	return 0;
}