#include <stdio.h>

int gcd(int a, int b){
	while(b){
		int t = a % b;
		a = b;  b = t;
	}
	return a;
}
int main(){
	int n, m; scanf("%d %d", &n, &m);
	printf("%d\n", m - gcd(n, m));
	return 0;
}