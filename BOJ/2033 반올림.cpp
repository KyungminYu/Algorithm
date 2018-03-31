#include <stdio.h>
int main(){
	int n; scanf("%d", &n);
	int d = 1;
	while(d * 10 < n){
		if(5 * d <= (n % (d * 10)))
			n += (d * 10);
		n -= (n % (d * 10));
		d *= 10;
	}
	printf("%d\n", n);
	return 0;
}