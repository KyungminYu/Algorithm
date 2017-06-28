#include <stdio.h>
#include <stdlib.h>
int main(){
	int n, a, ind, min;
	scanf("%d %d", &n, &a);
	ind = 1; min = 1e9;

	for(int i = 1; i <= n - 2; i++){
		if(abs(180 * i - a * n) < min){
			ind = i;
			min = abs(180 * i - a * n);
		}
	}
	printf("1 2 %d\n", n - (ind-1));
	return 0;
}