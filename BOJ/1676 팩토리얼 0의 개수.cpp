#include <stdio.h>

int main(){
	int n; scanf("%d", &n);
	int res = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 5; j <= n; j *= 5)
			res += ((i % j) == 0);
	}
	printf("%d\n", res);
	return 0;
}