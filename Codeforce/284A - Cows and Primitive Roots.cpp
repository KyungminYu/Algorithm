#include <stdio.h>

int main(){
	int p, cnt = 0;
	scanf("%d", &p);
	for (int i = 1; i < p; i++){
		bool flag = 1;
		long long x = i;
		for (int j = 0; j < p - 2; j++){
			if (x == 1)	flag = 0;
			x = (x * i) % p;
		}
		if (flag) cnt++;
	}	
	printf("%d\n", cnt);
	return 0;
}