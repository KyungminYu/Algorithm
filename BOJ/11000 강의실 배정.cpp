#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int> > st;
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int s, t; scanf("%d %d", &s, &t);
		st.push_back({s, t});	
	}
	sort(st.begin(), st.end());
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(st[0].second);
	for(int i = 1; i < n; i++){
		int s = st[i].first;
		int t = st[i].second;
		if((pq.top()) <= s) pq.pop();
		pq.push(t);
	}
	printf("%d\n", pq.size());
	while (!pq.empty()) pq.pop();
	return 0;
}