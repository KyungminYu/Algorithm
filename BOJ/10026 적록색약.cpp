#include <stdio.h>
#include <string.h>

char mp[101][101];
int chk[101][101];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, cnt;
int isCan(int r, int c){
    if(0 <= r && r < n && 0 <= c && c < n) return 1;
    return 0;
}
void dfs(char val, int r, int c, int RG){
    chk[r][c] = 1;
    for(int i = 0; i < 4; i++){
        int tr = r + dr[i];
        int tc = c + dc[i];
        if(!isCan(tr, tc)) continue;
        if(chk[tr][tc]) continue;
        if(val != mp[tr][tc]) {
            if(!RG) continue;
            else if(!((val == 'R' && mp[tr][tc] == 'G') || (val == 'G' && mp[tr][tc] == 'R'))) continue;
        }
        dfs(val, tr, tc, RG);
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            scanf(" %c", &mp[i][j]);
    }   
    cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(chk[i][j]) continue;
            dfs(mp[i][j], i, j, 0);
            cnt++;
        }
    }
    printf("%d ", cnt);
    memset(chk, 0, sizeof(chk));
    cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(chk[i][j]) continue;
            dfs(mp[i][j], i, j, 1);
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}