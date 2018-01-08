#include <stdio.h>
#include <queue>
using namespace std;

int prime[101];
int main(){
	int k, n; scanf("%d %d", &k, &n);
	priority_queue<long long> pq;
	for(int i = 0; i < k; i++){
		scanf("%d", &prime[i]);
		pq.push(-prime[i]);
	}
	long long res = 0;
	while(n--){
		res = -pq.top();
		pq.pop();
		for(int i = 0; i < k; i++){
			long long val = res * prime[i];
			pq.push(-val);
			if(res % prime[i] == 0) break;
		}
	}
	printf("%lld\n", res);
	return 0;
}