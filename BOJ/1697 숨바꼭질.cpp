#include <stdio.h>
#include <queue>
using namespace std;
int check[100001];
int dist[100001];
queue<int> q;
int main(){
	int N, D;
	scanf("%d %d", &N, &D);
	check[N] = 1;
	q.push(N);
	while (!q.empty()){
		int now = q.front();
		q.pop();
		if (0 <= now - 1 && check[now - 1] == 0){
			check[now - 1] = 1;
			q.push(now - 1);
			dist[now - 1] = dist[now] + 1;
		}
		if (now + 1 <= 100000 && check[now + 1] == 0){
			check[now + 1] = 1;
			q.push(now + 1);
			dist[now + 1] = dist[now] + 1;
		}
		if (now * 2 <= 100000 && check[now * 2] == 0){
			check[now * 2] = 1;
			q.push(now * 2);
			dist[now * 2] = dist[now] + 1;
		}
	}
	printf("%d\n", dist[D]);
	return 0;
}