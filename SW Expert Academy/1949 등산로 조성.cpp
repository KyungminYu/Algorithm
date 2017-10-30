#include <stdio.h>
#include <string.h>

int T, n, k;
int mp[9][9], chk[9][9];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int isCan(int r, int c){
	return (0 <= r && r < n && 0 <= c && c < n);
}
void dfs(int r, int c, int depth, int &len, int usek){
	chk[r][c] = 1;
	len = len < depth ? depth : len;
	for(int i = 0; i < 4; i++){
		int tr = r + dr[i];
		int tc = c + dc[i];
		if(!isCan(tr, tc)) continue;
		if(chk[tr][tc]) continue;
		if(mp[r][c] > mp[tr][tc])
			dfs(tr, tc, depth + 1, len, usek);
		else {
			if(!usek && mp[r][c] > mp[tr][tc] - k){
				int recover = mp[tr][tc];
				mp[tr][tc] = mp[r][c] - 1;
				dfs(tr, tc, depth + 1, len, 1);
				mp[tr][tc] = recover;
			}
		}
	}
	chk[r][c] = 0;
}
int main(){
	scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		scanf("%d %d", &n, &k);
		int mmax = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &mp[i][j]);
				mmax = mmax < mp[i][j] ? mp[i][j] : mmax;
			}
		}

		int ans = 0;
		for(int r = 0; r < n; r++){
			for(int c = 0; c < n; c++){
				if(mp[r][c] != mmax) continue;
				dfs(r, c, 1, ans, 0);
			}
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}