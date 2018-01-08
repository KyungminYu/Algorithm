#include <stdio.h>

int in[101];
int GCD(int u, int v){
	int t = u % v;
	while(t){
		u = v;
		v = t;
		t = u % v;
	}
	return v;
}
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &in[i]);
	for(int i = 1; i < n; i++){
		int gcd = GCD(in[0], in[i]);
		printf("%d/%d\n", in[0] / gcd, in[i] / gcd);
	}
	return 0;
}