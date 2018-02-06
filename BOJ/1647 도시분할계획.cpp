#include <stdio.h>
#include <algorithm>
using namespace std;

struct road {
	int a, b, c;
	road() {}
	void read() {scanf("%d %d %d", &a, &b, &c);}
	int operator < (road e) const { return c < e.c; }
}R[1000001];
int parent[100001];
int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
int main() {
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++) parent[i] = i;
	for (int i = 0; i < m; i++) R[i].read();
	sort(R, R + m);
		
	int res = 0;
	for (int i = 0; i < m && 2 < n; i++) {
		int a = find(R[i].a);
		int b = find(R[i].b);
		if (a != b) {
			n--;
			parent[b] = a;
			res += R[i].c;
		}
	}
	printf("%d\n", res);
	return 0;
}