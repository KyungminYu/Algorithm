#include <stdio.h>
int main(){
	int n, m, k, t = 0;
	scanf("%d %d %d", &n, &m, &k);
	while(n >= 2 && m >= 1 
		&& n + m - 3 >= k){
		n -= 2;	m--; t++;
	}
	printf("%d\n", t);
	return 0;
}