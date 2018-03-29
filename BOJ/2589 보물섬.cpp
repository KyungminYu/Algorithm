#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int map[51][51], chk[51][51];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
char in[51];
int n, m;

struct point{int r, c;};

int isCan(int r, int c){return (0 <= r && r < n && 0 <= c && c < m);}

void bfs(int sr, int sc, int& res){
	memset(chk, 0, sizeof(chk));
	queue<point> q;
	q.push({sr, sc});
	chk[sr][sc] = 1;
	int len = -1;
	while(!q.empty()){
		len++;
		int size= q.size();
		for(int i = 0; i < size; i++){
			int r = q.front().r;
			int c = q.front().c;
			q.pop();
			for(int d = 0; d < 4; d++){
				int tr = r + dr[d];
				int tc = c + dc[d];
				if(!isCan(tr, tc)) continue;
				if(!map[tr][tc]) continue;
				if(chk[tr][tc]) continue;
				q.push({tr, tc});
				chk[tr][tc] = 1;
			}
		}
	}
	res = max(res, len);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i< n; i++){
		scanf("%s", in);
		for(int j = 0; j < m; j++)
			map[i][j] = (in[j] == 'L');
	}
	int res = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(!map[i][j]) continue;
			bfs(i, j, res);
		}	
	}
	printf("%d\n", res);
	return 0;
}