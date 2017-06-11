#include <stdio.h>
int A[11];
int main(){
	int N, K, t, ans = 0;
	scanf("%d %d", &N, &K);
	for(int i = N - 1; i >= 0; i--) scanf("%d", &A[i]);
	for(int i = 0; i < N; i++){
		if(K == 0) break;
		if(K < A[i]) continue;
		t = K / A[i];
		ans += t;
		K -= t * A[i];
	}
	printf("%d\n", ans);
	return 0;
}