#include <stdio.h>
#include <map>
#include <queue>
using namespace std;

int main(){
	int n; scanf("%d", &n);
	map<long long, int> mp;
	for(int i = 0; i < n; i++){
		long long v; scanf("%lld", &v);
		mp[v]++;
	}
	priority_queue<pair<int, long long> > pq;
	for(auto it = mp.begin(); it != mp.end(); it++)
		pq.push({(*it).second, -(*it).first});
	printf("%lld\n", -pq.top().second);

	return 0;
}