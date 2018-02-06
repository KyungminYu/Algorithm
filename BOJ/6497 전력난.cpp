#include <stdio.h>
#include <algorithm>
using namespace std;

struct road {
	int x, y, z;
	road() {}
	void read() {scanf("%d %d %d", &x, &y, &z);}
	int operator < (road e) const {	return z < e.z;	}
}R[200001];
int parent[200001];
int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
int main() {
	while (1) {
		int m, n; scanf("%d %d", &m, &n);
		if (m == 0 && n == 0) break;
		for (int i = 0; i <= m; i++) parent[i] = i;
		int res = 0;
		for (int i = 0; i < n; i++) {
			R[i].read();
			res += R[i].z;
		}
		sort(R, R + n);
		for (int i = 0; i < n && 1 < m; i++) {
			int x = find(R[i].x);
			int y = find(R[i].y);
			if (x != y) {
				m--;
				parent[y] = x;
				res -= R[i].z;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}