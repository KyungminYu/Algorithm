#include <stdio.h>

int coin[] = {500, 100, 50, 10, 5, 1};
int main(){
	int P, t, cnt = 0;
	scanf("%d", &P);
	P = 1000 - P;
	for(int i = 0; i < 6 && 0 < P; i++){
		t = P / coin[i];
		cnt += t;
		P -= t * coin[i];
	}
	printf("%d\n", cnt);
	return 0;
}