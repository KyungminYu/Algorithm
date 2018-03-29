#include <stdio.h>

int board[129][129], ans[2], n;
int chk(int size, int r, int c){
	int clr = board[r][c];
	for(int i = r; i < r + size; i++){
		for(int j = c; j < c + size; j++){
			if(clr != board[i][j]) return -1;
		}
	}
	return clr;
}
void solve(int size, int r, int c){
	int clr = chk(size, r, c);
	if(clr != -1) {
		ans[clr]++;
		return;
	}
	solve(size / 2, r, c);
	solve(size / 2, r + size / 2, c);
	solve(size / 2, r, c + size / 2);
	solve(size / 2, r + size / 2, c + size / 2);
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			scanf("%d", &board[i][j]);
	}
	solve(n, 0, 0);
	printf("%d\n%d", ans[0], ans[1]);
	return 0;
}