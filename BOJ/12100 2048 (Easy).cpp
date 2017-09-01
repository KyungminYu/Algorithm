#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
int N;
vector<vector<int> > board;
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
void lineSum(vector<int> &l){
	for(int i = 0; i < l.size(); i++){
		if(i == l.size() - 1) continue;
		if(l[i] == l[i + 1]){
			l[i] += l[i + 1];
			l[i + 1] = 0;
		}
	}
}
int main(){
	scanf("%d", &N);
	board.resize(N);
	for(int i = 0; i < N; i++){
		board[i].resize(N);
		for(int j = 0; j < N; j++)
			scanf("%d", &board[i][j]);
	}

	queue<vector<vector<int> >> q;
	q.push(board); 
	int count = 5, mmax = 0;
	while(count-- >= 0){
		int qlen = q.size();
		while(qlen--) {
			vector<vector<int> > cur = q.front();
			q.pop();
			for(int i = 0; i < N; i++){
				for(int j = 0; j < N; j++)
					mmax = mmax > cur[i][j] ? mmax : cur[i][j];
			}
			for(int dir = 0; dir < 4; dir++){
				vector<vector<int> > moved(N);
				for(int i = 0; i < N; i++){
					moved[i].resize(N);
	 				for(int j = 0; j < N; j++)
						moved[i][j] = 0;
				}
				vector<int> line(N);
				if(dir == 0){ // up to down;
					for(int c = 0; c < N; c++){
						line.clear();
						for(int r = N - 1; r >= 0; r--){
							if(cur[r][c] == 0) continue;
							line.push_back(cur[r][c]);
						}
						lineSum(line);
						for(int r = N - 1, ind = 0; ind < line.size(); ind++){
							if(line[ind] == 0) continue;
							moved[r--][c] = line[ind];
						}
					}
				}	
				else if(dir == 1){// down to up;
					for(int c = 0; c < N; c++){
						line.clear();
						for(int r = 0; r < N; r++){
							if(cur[r][c] == 0) continue;
							line.push_back(cur[r][c]);
						}
						lineSum(line);
						for(int r = 0, ind = 0; ind < line.size(); ind++){
							if(line[ind] == 0) continue;
							moved[r++][c] = line[ind];
						}
					}
				}
				else if(dir == 2){// left to right;
					for(int r = 0; r < N; r++){
						line.clear();
						for(int c = N - 1; c >= 0; c--){
							if(cur[r][c] == 0) continue;
							line.push_back(cur[r][c]);
						}
						lineSum(line);
						for(int c = N - 1, ind = 0; ind < line.size(); ind++){
							if(line[ind] == 0) continue;
							moved[r][c--] = line[ind];
						}
					}	
				}
				else{ //right to left
					for(int r = 0; r < N; r++){
						line.clear();
						for(int c = 0; c < N; c++){
							if(cur[r][c] == 0) continue;
							line.push_back(cur[r][c]);
						}
						lineSum(line);
						for(int c = 0, ind = 0; ind < line.size(); ind++){
							if(line[ind] == 0) continue;
							moved[r][c++] = line[ind];
						}
					}	
				}
				q.push(moved);
			}
		}
	}
	printf("%d\n", mmax);

	return 0;
}