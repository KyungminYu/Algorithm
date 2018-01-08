#include <stdio.h>

int n, m;
int board[11][11];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int isCan(int r, int c){
	return (0 <= r && r < n && 0 <= c && c < m);
}
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char t; scanf(" %c", &t);
			board[i][j] = (t == '.' ? 1 : 0);
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int able = 0;
			if(!board[i][j]) continue;
			for(int d = 0; d < 4; d++){
				int tr = i + dr[d];
				int tc = j + dc[d];
				if(!isCan(tr, tc)) continue;
				if(board[tr][tc]) able++;
			}
			if(able < 2) {
				printf("1\n");
				return 0;
			}
		}
	}
	printf("0\n");
	return 0;
}