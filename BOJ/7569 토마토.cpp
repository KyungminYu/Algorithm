#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;

typedef struct { 
    int x, y, h;
} point;

int box[102][102][102];
int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dh[] = {0, 0, 0, 0, 1, -1};
int N, M, H, day, total;
queue<point> q;
int main(){
    scanf("%d %d %d", &N, &M, &H);
    memset(box, -1, sizeof(box));
    for(int h = 1; h <= H; h++){
        for(int i = 1; i <= M; i++){
            for(int j = 1; j <= N; j++){
                scanf("%d", &box[h][i][j]);
                if (box[h][i][j] == 1) q.push(point{i, j, h});
                else if (box[h][i][j] == 0) total++; 
            }
        }
    }
    while(!q.empty()){
        point p = q.front();
        q.pop();
        for(int i = 0; i < 6; i++){
            int tx = p.x + dx[i];
            int ty = p.y + dy[i];
            int th = p.h + dh[i];
            if(box[th][tx][ty] == 0){
                q.push(point{tx, ty, th});
                box[th][tx][ty] = box[p.h][p.x][p.y] + 1;
                total--;
            }
        }
        day = box[p.h][p.x][p.y] - 1;
    }
    if(total <= 0) printf("%d\n", day);
    else printf("-1\n");
    return 0;
}