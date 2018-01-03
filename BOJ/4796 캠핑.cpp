#include <stdio.h>
int main(){
	for(int t = 1; ;t++){
		int l, p, v;
		scanf("%d %d %d", &l, &p, &v);
		if(l == 0 && p == 0 && v == 0) break;
		printf("Case %d: %d\n"
			, t, (v % p < l ? v % p : l) + (v / p) * l);
	}
	return 0;
}