#include <stdio.h>
int a[101], phi[10001], vis[10001];
int Pow(int n, int p, int mod){
	int ret = 1;
	while(p){
		if(p & 1) ret = (ret * n) % mod;
		n = (n * n) % mod;
		p >>= 1;
	}
	return ret;
}
int euler_mod(int idx, int n, int mod) {  
    if (idx == n - 1) return a[idx] % mod;  
    int p = euler_mod(idx + 1, n, phi[mod]) + phi[mod];  
    return Pow(a[idx], p, mod);  
}  
int main(){
	int Case = 0, M, N, p;
    for (int i = 1; i <= 10000; i++) phi[i] = i;  
    for (int i = 2; i <= 10000; i++) {  
        if (vis[i]) continue;  
        for (int j = i; j <= 10000; j += i) {  
            phi[j] = phi[j] / i * (i - 1);  
            vis[j] = 1;  
        }  
    }  
	while(scanf("%d", &M) != NULL){
		scanf("%d", &N);
		for(int i = 0; i < N; i++)	scanf("%d", &a[i]);
		printf("Case #%d: %d\n", ++Case, euler_mod(0, N, M));
	}
	return 0;
}