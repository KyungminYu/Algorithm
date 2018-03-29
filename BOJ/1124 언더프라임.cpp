#include <stdio.h>

int prime[100001];
int main(){
	prime[0] = prime[1] = 1;
	for(int i = 2; i <= 100000; i++){
		if(prime[i]) continue;
		for(int j = i + i; j <= 100000; j += i){
			for(int k = j; k % i == 0; k /= i)
				prime[j]++;
		}
	}

	int a, b, ans = 0; scanf("%d %d", &a, &b);
	for(int i = a; i <= b; i++){
		if(prime[prime[i]] == 0) ans++; 
	}
	printf("%d", ans);

	return 0;
}