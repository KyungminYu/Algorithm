#include <stdio.h>
#define lld long long
int main(){
	int t; scanf("%d", &t);
	while(t--){
		lld x, y; scanf("%lld %lld", &x, &y);
		lld d = y- x, n = 1, l, h;
		while(1){
			l = n * (n - 1) + 1;
			h = n * (n + 1);
			if(l <= d && d <= h) break;
			n++;
		}
		printf("%lld\n", d <= n * n ? n * 2 - 1 : n * 2);
	}
	return 0;
}