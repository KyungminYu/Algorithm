#include <stdio.h>

int main(){
	int c, v0, v1, a, l, day, amount;
	scanf("%d %d %d %d %d", &c, &v0, &v1, &a, &l);
	day = 1; amount = v0;
	while(amount < c){
		v0 += a;
		if(v0 > v1) v0 = v1;
		amount -= l;
		if(amount < 0) amount = 0;
		amount += v0;
		day++;
	}
	printf("%d\n", day);
	return 0;
}