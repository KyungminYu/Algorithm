#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

struct edge {
	int s1, s2;
	double len;
	edge() {};
	edge(int s1, int s2, double len) {
		this->s1 = s1;
		this->s2 = s2;
		this->len = len;
	}
	int operator < (edge e) const {
		return len < e.len;
	}
}E[4951];
struct pos {
	double x, y;
	pos() {};
	void read() { scanf("%lf %lf", &x, &y); }
}S[101];
int parent[101];
int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

double dist(pos& p1, pos& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
		        (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
	int n, ind = 0; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		S[i].read();
		parent[i] = i;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) 
			E[ind++] = {i, j, dist(S[i], S[j])};
	}
	sort(E, E + ind);
	double res = 0.0;
	for (int i = 0; i < ind && 1 < n; i++) {
		int s1 = find(E[i].s1);
		int s2 = find(E[i].s2);
		if (s1 != s2) {
			n--;
			parent[s2] = s1;
			res += E[i].len;
		}
	}
	printf("%.2lf", res);
	return 0;
}