#include <stdio.h>
#define Min(a, b)((a) < (b) ? (a) : (b))
int main(){
	int n, m; scanf("%d %d", &n, &m);
	int set = 1e9, each = 1e9;
	for(int i = 0; i < m; i++){
		int s, e; scanf("%d %d", &s, &e);
		set = Min(s, set);
		each = Min(e, each);
	}
	set = Min(set, each * 6);
	int res = n / 6 * set + (n % 6) * each;
	if((n % 6) * each > set) 
		res = (n / 6 + 1) * set;
	printf("%d", res);

	return 0;
}