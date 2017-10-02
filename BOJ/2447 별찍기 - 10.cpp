#include <stdio.h>
char res[8000][8000];
int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
void solve(int n, int r, int c){
	if(n == 1){
        res[r][c]= '*';
        return;
    }
	if(n == 3){
		for(int i = 0; i < 8; i++) res[r + dr[i]][c + dc[i]] = '*';
		return;
	}
	int base = n / 3;
	for(int i = 0; i < 8; i++) solve(base, r + dr[i] * base, c + dc[i] * base);
}

int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) res[i][j] = ' ';
	solve(n, n / 2, n / 2);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%c", res[i][j]);
		printf("\n");
	}
	return 0;
}