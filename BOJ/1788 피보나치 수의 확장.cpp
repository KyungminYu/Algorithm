#include <stdio.h>

const int MOD = 1e9;
int fib[1000005];
int main(){
	fib[0] = 0; fib[1] = 1;
	for(int i = 2; i <= 1000000; i++)
		fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
	int n; scanf("%d", &n);
	if(n < 0 && n % 2 == 0) printf("-1\n");
	else if(n == 0) printf("0\n");
	else printf("1\n");
	printf("%d\n", fib[n < 0 ? -n : n]);

	return 0;
}