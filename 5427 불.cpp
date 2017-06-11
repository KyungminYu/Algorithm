#include <stdio.h>
#include <queue>
using namespace std;

char Map[1001][1001];
char cnt;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
int main(){
	int T;
	scanf("%d", &T);
	for (int t = 0; t <T; t++){
		int w, h, flag = 0, cnt = 0;
		queue<pair<int, int> > fire;
		queue<pair<int, int> > people;
		scanf("%d %d", &w, &h);
		for (int i = 0; i < h; i++){
			scanf("%s", &Map[i]);
			for (int j = 0; j < w; j++){
				if (Map[i][j] == '*')
					fire.push(make_pair(i, j));
				if (Map[i][j] == '@')
					people.push(make_pair(i, j));
			}
		}

		while (!people.empty()){
			cnt++;
			int flen = fire.size();
			int plen = people.size();

			for (int i = 0; i< flen; i++){
				int fx = fire.front().first;
				int fy = fire.front().second;
				fire.pop();
				for (int j = 0; j<4; j++){
					int tx = fx + dx[j];
					int ty = fy + dy[j];
					if (0 <= tx && tx < h && 0 <= ty && ty < w && Map[tx][ty] == '.'){
						fire.push(make_pair(tx, ty));
						Map[tx][ty] = '*';
					}
				}
			}
			for (int i = 0; i < plen; i++){
				int px = people.front().first;
				int py = people.front().second;
				people.pop();

				if (px == 0 || px == h - 1 || py == 0 || py == w - 1){
					flag = 1;
					break;
				}
				for (int j = 0; j < 4; j++){
					int tx = px + dx[j];
					int ty = py + dy[j];
					if(Map[tx][ty] == '.'){
						people.push(make_pair(tx, ty));
						Map[tx][ty] = '@';
					}
				}
			}
			if (flag) break;
		}
		if (flag == 0)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", cnt);
	}
	return 0;
}