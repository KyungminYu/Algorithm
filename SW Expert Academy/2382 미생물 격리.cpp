#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct state{
	int r, c, num, dir, ind;
};

queue<state> q;
vector<pair<int, int> > mp[101][101];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int isBound(int r, int c, int n){
	return (r == 0 || r == (n - 1) || c == 0 || c == (n - 1));
}

int main(){
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++){
		int n, m, k; scanf("%d %d %d", &n, &m, &k);
		for(int i = 0; i < k; i++){
			int r, c, num, dir;
			scanf("%d %d %d %d", &r, &c, &num, &dir);
			q.push({r, c, num, dir});
		}
		int timer = 0;
		while(!q.empty() && timer < m) {
			timer++;
			int qlen = q.size();
			for(int i = 0; i <= n; i++){
				for(int j = 0; j <= n; j++)
					mp[i][j].clear(); 
			}
			for(int i = 0; i < qlen; i++){

				int curR = q.front().r;
				int curC = q.front().c;
				int num = q.front().num;
				int dir = q.front().dir;
		    	q.pop();

		    	int tr = curR + dr[dir - 1]; 
		    	int tc = curC + dc[dir - 1]; 

				if(isBound(tr, tc, n)){
					num /= 2;
					if(dir == 1) dir = 2;
					else if(dir == 2) dir = 1;
					else if(dir == 3) dir = 4;
					else if(dir == 4) dir = 3;
				}
		    	mp[tr][tc].push_back({num, dir});
			}
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					int exist = 0, dir = 0, mx = 0, sum = 0;
					for(int k = 0; k < mp[i][j].size(); k++){
						exist = 1;
						sum += mp[i][j][k].first;
						if(mx < mp[i][j][k].first){
							mx = mp[i][j][k].first;
							dir = mp[i][j][k].second;
						}

					}
					if(!exist) continue;
					q.push({i, j, sum, dir});
				}
			}
		}
		int res = 0;
		while(!q.empty()) {
		    res += q.front().num;
		    q.pop();
		}
		printf("#%d %d\n", t, res);
	}
	return 0;
}