#include <stdio.h>
int cnt[10001];
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int t; scanf("%d", &t);
		cnt[t]++;
	}
	for(int i = 1; i <= 10000; i++){
		while(cnt[i]--) printf("%d\n", i);
    }
	return 0;
}