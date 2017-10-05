#include <stdio.h>
char board[51][51];
int solve(int r, int c){
	int cnt = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if((i % 2 == j % 2 ? 'W' : 'B') 
				== board[r + i][c + j]) cnt++;
		}
	}
	return cnt < (64 - cnt) ? cnt : (64 - cnt);
}
int main(){
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) scanf(" %c", &board[i][j]);
	}

	int res = 1e9;
	for(int i = 0; i <= n - 8; i++){
		for(int j = 0; j <= m - 8; j++){
			int ret = solve(i, j);
			res = res < ret ? res : ret;
		}
	}
	printf("%d\n", res);
	return 0;
}