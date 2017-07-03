#include <stdio.h>
#include <queue>
using namespace std;
int main(){
	int n, t;
	priority_queue<int> pq;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &t);
		if(t == 0) {
			if(pq.empty()) printf("0\n");
			else{
				printf("%d\n", pq.top());
				pq.pop();
			}
		}
		else pq.push(t);

	}
	return 0;
}