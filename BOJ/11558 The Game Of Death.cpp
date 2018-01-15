#include <stdio.h>
int player[10001];
int main(){
	int T;scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &player[i]);
		int res = 1, cur = 1;
		while(player[cur] != n && res < n){
			res++;
			cur = player[cur];
		}
		printf("%d\n", res == n ? 0 : res);
	}
	return 0;
}