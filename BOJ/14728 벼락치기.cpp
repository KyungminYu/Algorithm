#include <stdio.h>
#include <algorithm>
using namespace std;
struct problem{
	int k, s;
	void read(){scanf("%d %d", &k, &s);}
}p[101];
int knap[101][10001];
int main(){
	int n, t; scanf("%d %d", &n, &t);
	for(int i = 1; i <= n; i++)
		p[i].read();
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= t; j++){
			knap[i][j] = knap[i - 1][j];
			if(p[i].k <= j) 
				knap[i][j] = max(knap[i][j], knap[i - 1][j - p[i].k] + p[i].s);
		}
	}
	printf("%d", knap[n][t]);
	return 0;
}