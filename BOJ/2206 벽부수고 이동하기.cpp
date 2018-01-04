#include <stdio.h>
#include <queue>
using namespace std;

int board[1001][1001];
int chk[1001][1001][2];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, m; 
struct pos{ int r, c, crashed; };
int isCan(int r, int c){
	return (1 <= r && r <= n && 1 <= c && c <= m);
}
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++){
			char t; scanf(" %c", &t);
			board[i][j] = (t == '0');
		}	
	}
	queue<pos> q;
	q.push({1, 1, 0});
	chk[1][1][0] = 1;
	int dist = 1;	

	while(!q.empty()){
		int size = q.size();
		int arrival = 0;
		while(size--){

			int r = q.front().r;
			int c = q.front().c;
			int crached = q.front().crashed;
			q.pop();
			if(r == n && c == m){
				arrival = 1;
				break;
			}
			for(int i = 0; i < 4; i++){
				int tr = r + dr[i];
				int tc = c + dc[i];
				if(!isCan(tr, tc)) continue;
				if(chk[tr][tc][crached]) continue;
				if(board[tr][tc]){
					chk[tr][tc][crached] = 1;		
					q.push({tr, tc, crached});
				}
				else{
					if(crached) continue;	
					chk[tr][tc][1] = 1;	
					q.push({tr, tc, 1});
				}			
			}
		}
		if(arrival) break;
		dist++;
	}
	if(chk[n][m][0] || chk[n][m][1])
		printf("%d", dist);
	else printf("-1");
	return 0;
}