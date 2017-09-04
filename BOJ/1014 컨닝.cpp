#include <stdio.h>
#include <vector>
using namespace std;

#define MAXN 101
char mp[10][10];
int even[MAXN], odd[MAXN], chk[MAXN]; // 짝, 홀
int dr[] = { 0, 0, -1, -1 };
int dc[] = { 1, -1, 1, -1 };
vector<int> G[MAXN];
vector<pair<int, int> > vertex[2];	
int isCan(int r, int c, int n, int m){
	return (0 <= r && r < n && 0 <= c && c < m);
}
int getId(int r, int c){
	return r * 10 + c;
}
void addEdge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
int dfs(int v){
	chk[v] = 1;
	for(int i = 0; i < G[v].size(); i++){
		int nxt = G[v][i];
		if(odd[nxt] == -1 || !chk[odd[nxt]] && dfs(odd[nxt])){
            odd[nxt] = v;
            even[v] = nxt;
            return 1;
        }
	}
	return 0;
}
int main(){
	int T; scanf("%d", &T);
	while(T--){
		int n, m; scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++)
				scanf(" %c ", &mp[i][j]);
		}
		vertex[0].clear(); vertex[1].clear();
		for(int i = 0; i < MAXN; i++) {
			G[i].clear();
			odd[i] = even[i] = -1;
		}

		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(mp[i][j] == 'x') continue;
				vertex[j % 2].push_back({i, j});
				for(int k = 0; k < 4; k++){
					int tr = i + dr[k];
					int tc = j + dc[k];
					if(!isCan(tr, tc, n, m)) continue;
					if(mp[tr][tc] == 'x') continue;
					addEdge(getId(i, j), getId(tr, tc));
 				}
			}
		}
		int res = 0;
		for(int i = 0; i < vertex[0].size(); i++){
			pair<int, int> nxt = vertex[0][i];
			if(even[getId(nxt.first, nxt.second)] == -1){
				for(int c = 0; c < MAXN; c++) chk[c] = 0;
				if(dfs(getId(nxt.first, nxt.second))) res++; // 연결된데는 컨닝 가능한영역.
			}
		}
		printf("%d\n", vertex[0].size() + vertex[1].size() - res); // 전체에서 컨닝가능 최대 영역을 빼 주어야 한다
	}

	return 0;
}