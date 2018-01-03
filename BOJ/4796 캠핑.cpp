#include <stdio.h>
int main(){
	for(int t = 1; ;t++){
		int l, p, v;
		scanf("%d %d %d", &l, &p, &v);
		if(!l && !p && !v) break;
		printf("Case %d: %d\n"
			, t, (v % p < l ? v % p : l) + (v / p) * l);
	}
	return 0;
}