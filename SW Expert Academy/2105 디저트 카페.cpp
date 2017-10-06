#pragma GCC optimize ("O2")
#include <stdio.h>
#define Max(a, b){(a) > (b) ? (a) : (b)}
int mp[21][21], chk[21][21], vis[101];
int dr[] = { 1, 1, -1, -1 };
int dc[] = { 1, -1, -1, 1 };

int isCan(int r, int c, int n){
	return (0 <= r && r < n && 0 <= c && c < n);
}
int solve(int r, int c, int n){
	int ret = -1;
	for(int a = 1; a < n; a++){
		for(int b = 1; b < n; b++){
			if(!isCan(r + a, c + a, n) || !isCan(r + b, c - b, n)
				|| !isCan(r + a + b, c + a - b, n)) continue;
			for(int i = 0; i <= 100; i++) vis[i] = 0;
			int able = 1;
			int tr = r, tc = c;
			int len[2] = {a, b};
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < len[i % 2]; j++){
					tr += dr[i], tc += dc[i];
					if(!vis[mp[tr][tc]]) vis[mp[tr][tc]] = 1;
					else{ able = 0; break; }
				}
				if(!able) break;
			}
			if(!able) continue;
			ret = Max(ret, (a + b) * 2);
		}	
	}
	return ret;
}

int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				scanf("%d", &mp[i][j]);
		}
		int ans = -1;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				ans = Max(ans, solve(i, j, n));
		}
		if(ans == 0) ans = -1;
		printf("#%d %d\n", t, ans);
	}
	return 0;
}