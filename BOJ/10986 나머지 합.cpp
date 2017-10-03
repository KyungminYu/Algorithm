#include <stdio.h>
int A[1000001];
int C[1001];
int main(){
	int N, M, S;
	scanf("%d %d", &N, &M);
	C[0] = 1;
	S = 0;
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		S += A[i];
		S%=M;
		C[S]++;
	}
	long long result = 0;
	for (int i = 0; i < M; i++){
		result += (long long)C[i] * (long long)(C[i] - 1) / 2LL;
	}
	printf("%lld\n", result);
	return 0;
}