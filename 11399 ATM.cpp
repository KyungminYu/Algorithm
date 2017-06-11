#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int P[1001];
int cmp(int a, int b){return a < b;}
int main(){
	int N, sum = 0;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) scanf("%d", &P[i]);
	sort(P + 1, P + N + 1, cmp);
	for(int i = 1; i <= N; i++){
		P[i] += P[i-1];
		sum+=P[i];
	}
	printf("%d\n", sum);
	return 0;
}