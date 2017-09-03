#pragma GCC optimize("O2")
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

char mp[51][51];
int chk[51][51][2];
int dr[] = { 0, 0, 1, -1, 0 };
int dc[] = { 1, -1, 0, 0, 0 };
int dv[] = { 0, 0, 0, 0, 1  };
int ar[] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
int ac[] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
int n;
struct point{
	int r, c, dir;
	point(){};
	point(int r, int c, int dir){
		this->r = r;
		this->c = c;
		this->dir = dir;
	}
};
point s, e;
int isCan(int r, int c){
	return (0 <= r && r < n && 0 <= c && c < n);
}
int isCanMove(int r, int c, int dir, int opt){
	r += dr[opt];
	c += dc[opt];
	if(dir) return (isCan(r, c + 1) && isCan(r, c - 1) && mp[r][c] != '1' && mp[r][c + 1] != '1' && mp[r][c - 1] != '1');
	return (isCan(r + 1, c) && isCan(r - 1, c) && mp[r][c] != '1' && mp[r + 1][c] != '1' && mp[r - 1][c] != '1');
}
int isNothingAround(int r, int c){
	for(int i = 0; i < 9; i++){
		if(!isCan(r + ar[i], c + ac[i])) return 0;
		if(mp[r + ar[i]][c + ac[i]] == '1') return 0;
	}
	return 1;
}
int isAvailable(point p, int opt) {
    int r = p.r, c = p.c, dir = p.dir;
    if (opt == 4) return isNothingAround(r, c);
    else return isCanMove(r, c, dir, opt);
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			scanf(" %c ", &mp[i][j]);
	} 

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(mp[i][j] == 'B'){
				if(isCan(i - 1, j) && isCan(i + 1, j) && mp[i - 1][j] == 'B' && mp[i + 1][j] == 'B') s = point(i, j, 0);
				if(isCan(i, j - 1) && isCan(i, j + 1) && mp[i][j - 1] == 'B' && mp[i][j + 1] == 'B') s = point(i, j, 1);
			}
			if(mp[i][j] == 'E'){
				if(isCan(i - 1, j) && isCan(i + 1, j) && mp[i - 1][j] == 'E' && mp[i + 1][j] == 'E') e = point(i, j, 0);
				if(isCan(i, j - 1) && isCan(i, j + 1) && mp[i][j - 1] == 'E' && mp[i][j + 1] == 'E') e = point(i, j, 1);
			}
		}
	}
	queue<point> q;
	chk[s.r][s.c][s.dir] = 1;
	q.push(s);
	int res = 0;
	while(!q.empty()){
		int qlen = q.size();
		while(qlen--){
			point cur = q.front();
			q.pop();
			if(cur.r == e.r && cur.c == e.c && cur.dir == e.dir) {
				printf("%d\n", res);
				return 0;
			}
			for(int i = 0; i < 5; i++){
				if(!isAvailable(cur, i)) continue;
				int tr = cur.r + dr[i];
				int tc = cur.c + dc[i];
				int tv = cur.dir ^ dv[i];
				if(chk[tr][tc][tv]) continue;
				chk[tr][tc][tv] = 1;
				q.push(point(tr, tc, tv));
			}
		}
		res++;
	}
	printf("0\n");
	return 0;
}