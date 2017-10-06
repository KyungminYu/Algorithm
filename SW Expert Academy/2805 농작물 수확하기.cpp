#include <stdio.h>
#include <stdlib.h>
int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		int ans = 0;
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++){
			int k = n / 2;
			for(int j = 0; j < n; j++){
				int limit = abs(i - k) + abs(j - k);
				int val; scanf("%1d", &val);
				if(limit > k) continue;
				ans += val;
			}
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}