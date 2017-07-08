#include <stdio.h>

int map[51][51];
int dw[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int dh[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
void dfs(int h, int w, int H, int W){
    map[h][w] = 0;
    for(int i = 0; i < 8; i++){
        int th = h + dh[i];
        int tw = w + dw[i];
        if(map[th][tw] && 0 <= tw && tw < W && 0 <= th && th < H)
            dfs(th, tw, H, W);
    }
}
int main(){
    int w, h, cnt;
    while(scanf("%d %d", &w, &h)){
        if(w == 0 && h == 0) break;
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++) scanf("%d", &map[i][j]);
        }
        cnt = 0;
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                if(map[i][j]) {
                    dfs(i, j, h, w);
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}