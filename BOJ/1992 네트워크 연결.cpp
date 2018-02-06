#include <stdio.h>
#include <algorithm>
using namespace std;

struct edge {
	int a, b, c;
	edge() {}
	void read() {
		scanf("%d %d %d", &a, &b, &c);
	}
	int operator < (edge e) const {
		return c < e.c;
	}
}E[100001];
int parent[1001];
int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		parent[i] = i;
	for (int i = 0; i < m; i++)
		E[i].read();
	sort(E, E + m);

	int res = 0;
	for (int i = 0; i < m && 1 < n; i++) {
		int a = E[i].a;
		int b = E[i].b;
		int c = E[i].c;
		a = find(a); b = find(b);
		if (a != b) {
			n--;
			parent[b] = a;
			res += c;
		}
	}
	printf("%d", res);

	return 0;
}