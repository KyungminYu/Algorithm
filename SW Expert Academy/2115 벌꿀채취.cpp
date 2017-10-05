#include <stdio.h>
int honey[11][11];
int Max(int n1, int n2){
	if(n1 > n2) return n1;
	return n2;
}
int profit(int row, int col, int m, int C){
	int ret = 0;
	for(int bit = 0; bit < (1 << m); bit++){
		int sum = 0, limit = C;
		for(int i = 0; i < m; i++){
			if(bit & (1 << i)){
				sum += (honey[row][col + i] * honey[row][col + i]);
				limit -= honey[row][col + i];
			}
		}
		if(limit >= 0) ret = Max(ret, sum);
	}
	return ret;
}
int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		int n, m, c;
		scanf("%d %d %d", &n, &m, &c);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++) 
				scanf("%d", &honey[i][j]);
		}
		int res = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j <= n - m; j++){
				int tmp = profit(i, j, m, c);
				for(int k = 0; k < n; k++){
					for(int l = 0; l <= n - m; l++){
						if(i == k 
							&& ((l + m > j) || (j + m > l))) continue;
						res = Max(res, tmp + profit(k, l, m, c));
					}
				}
			}
		}
		printf("#%d %d\n", t, res);
	}
	return 0;
}