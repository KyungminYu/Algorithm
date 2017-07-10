#include <stdio.h>

int n, range;
int mp[101][101], chk[101][101][101];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
void dfs(int r, int c, int depth){
    chk[depth][r][c] = 1;
    for(int i = 0; i < 4; i++){
        int tr = r + dr[i];
        int tc = c + dc[i];
        if(chk[depth][tr][tc] || mp[tr][tc] <= depth) continue;
        dfs(tr, tc, depth);
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &mp[i][j]);
            if(range < mp[i][j]) range = mp[i][j];
        }
    }
    int cnt, ans = -1;
    for(int i = 0; i <= range; i++){
        cnt = 0;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(chk[i][j][k] || mp[j][k] <= i) continue;
                dfs(j, k, i);
                cnt++;
            
            }
        }
        if(ans < cnt) ans = cnt;
    }
    printf("%d\n", ans);
    return 0;
}