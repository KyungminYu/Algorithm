#include <stdio.h>
#include <queue>
using namespace std;

struct point{
	int r, c;
};
queue<point> q;
int board[101][101];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, -1, 0, 1 };
// 상 = 0 좌 = 1 하 = 2 우 = 3
int isCan(int r, int c, int n){
	return (1 <= r && r <= n && 1 <= c && c <= n);
}
int main(){
	int n; scanf("%d", &n);
	int k; scanf("%d", &k);
	for(int i = 0; i < k; i++){
		int r, c; scanf(" %d %d", &r, &c);
		board[r][c] = 2; // apple
	}
	int l; scanf("%d", &l);
	int timer = 0;
	int hR = 1, hC = 1, tR, tC, dir = 3, stop = 0;
	board[1][1] = 1; // snake
	q.push({hR, hC});
	for(int i = 0; i < l; i++){
		int x; scanf(" %d", &x);
		while(timer < x){
			timer++;
			hR += dr[dir];
			hC += dc[dir];
			tR = q.front().r;
			tC = q.front().c;
			// Boundary Check
			if(!isCan(hR, hC, n) || board[hR][hC] == 1) {
				stop = 1;
				break;
			}
			if(board[hR][hC] == 0){
				board[tR][tC] = 0;
				q.pop();
			} 
			q.push({hR, hC});
			board[hR][hC] = 1;
		}
		if(stop) break;
		char c; scanf(" %c", &c);
		dir += 4;
		if(c == 'L') dir++;
		else dir--;
		dir %= 4;
	}
	while(!stop){
		timer++;
		hR += dr[dir];
		hC += dc[dir];
		// Boundary Check
		if(!isCan(hR, hC, n) || board[hR][hC] == 1) {
			stop = 1;
			break;
		}
	}
	printf("%d\n", timer);
	return 0;
}