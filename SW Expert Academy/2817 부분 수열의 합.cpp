#include <stdio.h>
#include <algorithm>
using namespace std;
int A[21];
int cmp(int n1, int n2){
	return n1 < n2;
}
int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		int n, k; scanf("%d %d", &n, &k);
		for(int i = 0; i < n; i++) scanf("%d", &A[i]);
		sort(A, A + n, cmp);
		int len = 0;
		while(A[len] <= k && len < n) len++;
		int ans = 0;
		for(int bit = 1; bit < (1 << len); bit++){
			int sum = 0, tbit = bit, ind = 0, pass = 0;
			while(tbit){
				if(tbit & (1 << ind)){
					tbit -= (1 << ind);
					sum += A[ind];
				}
				if(sum > k) {
					pass = 1;
					break;
				}
				ind++;
			}	
			if(pass) continue;
			if(sum == k) ans++;
		}

		printf("#%d %d\n", t, ans);
	}

	return 0;
}