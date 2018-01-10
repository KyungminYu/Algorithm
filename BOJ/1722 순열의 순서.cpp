#include <stdio.h>
int in[22], chk[22];
int N, O;
long long factorial[22];
void permutation(int n, long long k){
	if(n == 1){
		for(int i = 1; i <= N + 1; i++){
			if(!chk[i]) {
				printf("%d\n", i);
				return;
			}
		}
	}
	else{
		for(int i = 1; i <= N + 1; i++){
			if(chk[i]) continue;
			if(k <= factorial[n - 1]){
				printf("%d ", i);
				chk[i] = 1;	
				permutation(n - 1, k);
				return;
			}
			k -= factorial[n - 1];
		}
	}
}
long long nth(long long k, int n){
	long long tmp = 0;
	// 1개 남은 경우
	if(k == N - 1) return 1;
	for(int i = 1; i <= N + 1; i++){
		if(chk[i]) continue;
		if(i == in[k]){
			chk[i] = 1;
			return nth(k + 1, n - 1) + tmp;
		}
		tmp += factorial[n - 1];
	}
}
int main(){
	factorial[0] = 1;
	for(int i = 1; i <= 20; i++)
		factorial[i] = factorial[i - 1] * i;
	
	scanf("%d %d", &N, &O);
	if(O == 1){
		long long k; 
		scanf("%lld", &k);
		permutation(N, k);
	}
	else if(O == 2){
		for(int i = 0; i < N; i++)
			scanf("%d", &in[i]);
		printf("%lld\n", nth(0, N));
	}
	return 0;
}