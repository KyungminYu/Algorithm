#include <stdio.h>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
char mp[302][302];
int mine[302][302], chk[302][302];
int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int n; 

int isCan(int r, int c){
	return (1 <= r && r <= n && 1 <= c && c <= n);
}

void dfs(int r, int c){
	chk[r][c] = 1;
	if(mine[r][c] != 0)	return;
	for(int i = 0; i < 8; i++){
		int tr = r + dr[i];
		int tc = c + dc[i];
		if(!isCan(tr, tc)) continue;
		if(chk[tr][tc]) continue;
		dfs(tr, tc);
	}
}
int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		scanf("%d", &n);
		for(int i = 0; i <= n + 1; i++){
			for(int j = 0; j <= n + 1; j++) {
				mp[i][j] = '.';
				chk[i][j] = 0;
			}
		}		
		for(int i = 1; i <= n; i++)
			scanf("%s", mp[i] + 1);

		vector<pair<int, pair<int, int> > > v;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				mine[i][j] = 0;
				chk[i][j] = (mp[i][j] == '*');
				for(int k = 0; k < 8; k++){
					int tr = i + dr[k];
					int tc = j + dc[k];
					if(mp[tr][tc] == '*') mine[i][j]++;
				}
				v.push_back({mine[i][j], {i, j}});
			}
		}
		sort(v.begin(), v.end());
		int clk = 0;
		for(int i = 0; i < v.size(); i++){
			int r = v[i].second.first;
			int c = v[i].second.second;
			if(chk[r][c]) continue;
			dfs(r, c);
			clk++;
		}
		printf("#%d %d\n", t, clk);
	}

	return 0;
}