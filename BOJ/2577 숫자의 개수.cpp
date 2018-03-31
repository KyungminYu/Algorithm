#include <stdio.h>
int cnt[10];
int main(){
	int n = 1;
	for(int i = 0; i < 3; i++){
		int t; scanf("%d", &t);
		n *= t;
	}
	while(n){
		cnt[n % 10]++;
		n /= 10;
	}
	for(int i = 0; i <= 9; i++) printf("%d\n", cnt[i]);
	return 0;
}