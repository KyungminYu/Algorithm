#include <stdio.h>
#include <algorithm>
using namespace std;
pair<int, int> P[100000];
pair<int, int> T[100000];

bool x_compare(pair<int, int> &p1, pair<int, int> &p2) {return p1.first < p2.first;}
int dist(pair<int, int> &p1, pair<int, int> &p2) {	return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);}
int merge(int delta,int pivot, int ind) {
	int mmin = 1e9, t_size = 0;
	for (int i = 0; i < ind; i++) {
		if ((pivot - T[i].first) * (pivot - T[i].first) <= delta)
			T[t_size++] = T[i];
	}
	for (int i = 0; i < t_size; i++) {
		for (int j = i + 1; j < t_size && j <= i + 6; j++)
			mmin = min(mmin, dist(T[i], T[j]));
	}
	return mmin;
}
int closestPair(int s, int e) {
	if (s == e)	return 1e9;
	if (e - s == 1) {
		if (P[s].second > P[e].second)
			swap(P[s], P[e]);
		return dist(P[s], P[e]);
	}
	int mid = (s + e) / 2;
	int pivot = P[mid].first;
	int delta = min(closestPair(s, mid), closestPair(mid + 1, e));
	int lptr, rptr, ind;
	lptr = s, rptr = mid + 1, ind = 0;
	while (lptr <= mid && rptr <= e) {
		if (P[lptr].second < P[rptr].second) T[ind++] = P[lptr++];
		else T[ind++] = P[rptr++];
	}
	while (lptr <= mid) T[ind++] = P[lptr++];
	while (rptr <= e)	T[ind++] = P[rptr++];
	for (int i = s; i <= e; i++) 
		P[i] = T[i - s];
	int mmin = merge(delta, pivot, ind);
	return min(delta, mmin);;
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &P[i].first, &P[i].second);
	sort(P, P+n, x_compare);
	printf("%d\n", func(0, n - 1));
	return 0;
}