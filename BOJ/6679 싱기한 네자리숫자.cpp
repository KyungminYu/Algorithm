#include <stdio.h>
int Sum(int n, int mod){
	int ret = 0;
	while(n){
		ret += n % mod;
		n /= mod;
	}
	return ret;
}
int isSame(int n){
	int Dec = Sum(n, 10);
	int Duo = Sum(n, 12);
	int Hex = Sum(n, 16);
	if(Dec == Duo && Duo == Hex) return 1;
	return 0;
}
int main(){
	for(int num = 1000; num < 10000; num++){
		if(isSame(num))
			printf("%d\n", num);
	}
	return 0;
}