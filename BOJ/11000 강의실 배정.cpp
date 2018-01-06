#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int, int> > time;
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int s, t; scanf("%d %d", &s, &t);
		time.push_back({s, 1});
		time.push_back({t, -1});
	}
	sort(time.begin(), time.end());
	int res = 0, s = 0;
	for(int i = 0; i < time.size(); i++){
		res = max(res, s);
		s += time[i].second;
	}
	printf("%d", res);
	return 0;
}