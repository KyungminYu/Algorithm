n#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
int T, n, m, sR, sC, l;
int mp[51][51], chk[51][51];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
//           우 좌 상 하
int isCan(int r, int c){
	return (0 <= r && r < n && 0 <= c && c < m);
}
int isConnected(int state1, int state2, int d){
	if(state2 == 0) return 0;
	if(d == 0){ // 우
		if(state1 == 2 || state1 == 6 || state1 == 7) return 0;
		if(state2 == 2 || state2 == 4 || state2 == 5) return 0;
	}
	else if(d == 1){ // 좌
		if(state1 == 2 || state1 == 4 || state1 == 5) return 0;
		if(state2 == 2 || state2 == 6 || state2 == 7) return 0;
	}
	else if(d == 2){ // 상
		if(state1 == 3 || state1 == 4 || state1 == 7) return 0;
		if(state2 == 3 || state2 == 5 || state2 == 6) return 0;
	}
	else if(d == 3){ // 하
		if(state1 == 3 || state1 == 5 || state1 == 6) return 0;
		if(state2 == 3 || state2 == 4 || state2 == 7) return 0;
	}
	return 1;
}
int main(){
	scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		scanf("%d %d %d %d %d", &n, &m, &sR, &sC, &l);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				scanf("%d", &mp[i][j]);
				chk[i][j] = 0;
			}
		}
		queue<pair<int, int> > q;
		chk[sR][sC] = 1;
		q.push({sR, sC});
		l--;
		while(l-- && !q.empty()){
			int qlen = q.size();
			for(int i = 0; i < qlen; i++){
				int cR = q.front().first, cC = q.front().second;
				q.pop();
				for(int d = 0; d < 4; d++){
					int tr = cR + dr[d], tc = cC + dc[d];
					if(!isCan(tr, tc)) continue;
					if(!isConnected(mp[cR][cC], mp[tr][tc], d)) continue;
					if(chk[tr][tc]) continue;
					chk[tr][tc] = 1;
					q.push({tr, tc});
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++) ans += chk[i][j];
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}