#include <stdio.h>
const int INF = 1e9 + 7;
int num[12], op[4];
int n, mmin, mmax;
void solve(int depth, int val, int plus, int minus, int multi, int divide) {
	if (depth >= n) {
		mmin = mmin > val ? val : mmin;
		mmax = mmax < val ? val : mmax;
		return;
	}
	if (plus > 0)	solve(depth + 1, val + num[depth], plus - 1, minus, multi, divide);
	if (minus > 0)	solve(depth + 1, val - num[depth], plus, minus - 1, multi, divide);
	if (multi > 0)	solve(depth + 1, val * num[depth], plus, minus, multi - 1, divide);
	if (divide > 0) solve(depth + 1, val / num[depth], plus, minus, multi, divide - 1);
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
	scanf("%d %d %d %d", &op[0], &op[1], &op[2], &op[3]);
	mmin = INF;	mmax = -INF;
	solve(1, num[0], op[0], op[1], op[2], op[3]);
	printf("%d\n%d\n", mmax, mmin);
	return 0;
}