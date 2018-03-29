#include <stdio.h>

int main(){
	int n, l; scanf("%d %d", &n, &l);
	while(l <= 100){
		int val = n - l * (l - 1) / 2;
		if(val < 0) break;
		if(val % l) l++;
		else{
			int s = val / l;
			for(int i = 0; i < l; i++)
				printf("%d ", s++);
			return 0;
		}
	}
	printf("-1");
	return 0;
}