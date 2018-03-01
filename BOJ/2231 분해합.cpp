#include <stdio.h>

int main(){
	int n; scanf("%d", &n);
	for(int res = 1; res <= 1000000; res++){
		int sum = res, tmp = res;
		while(tmp){
			sum += (tmp % 10);
			tmp /= 10;
		}
		if(sum == n) {
			printf("%d", res);
			return 0;
		}
	}
	printf("0");
	return 0;
}