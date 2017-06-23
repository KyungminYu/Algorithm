#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;

int box[1002][1002];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int N, M, day, total;
queue<pair<int, int> > q;
int main(){
    scanf("%d %d", &N, &M);
    memset(box, -1, sizeof(box));
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            scanf("%d", &box[i][j]);
            if (box[i][j] == 1) q.push(make_pair(i, j));
            else if (box[i][j] == 0) total++; 
        }
    }
    while(!q.empty()){
        int x = q.front().first; 
        int y = q.front().second; 
        q.pop();
        for(int i = 0; i < 4; i++){
            int tx = x + dx[i];
            int ty = y + dy[i];
            if(box[tx][ty] == 0){
                q.push(make_pair(tx, ty));
                box[tx][ty] = box[x][y] + 1;
                total--;
            }
        }
        day = box[x][y] - 1;
    }
    if(total <= 0) printf("%d\n", day);
    else printf("-1\n");
    return 0;
}