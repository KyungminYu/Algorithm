#include <stdio.h>

char space[101][101][101];
int chk[101][101][101];
int dx[] = { 0, 0, 0, 0, 1, -1 };
int dy[] = { 0, 0, 1, -1, 0, 0 };
int dz[] = { 1, -1, 0, 0, 0, 0 };
int n;
int isCan(int x, int y, int z){
    if(1 <= x && x <= n && 1 <= y && y <= n && 1 <= z && z <= n) return 1;
    return 0;
}
void dfs(int x, int y, int z){
    chk[x][y][z] = 1;
    for(int i = 0; i < 6; i++){
        int tx = x + dx[i];
        int ty = y + dy[i];
        int tz = z + dz[i];
        if(!isCan(tx, ty, tz)) continue;
        if((chk[tx][ty][tz]) || (space[tx][ty][tz] != '*')) continue;
        dfs(tx, ty, tz);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++)
                scanf(" %c", &space[i][j][k]);
        }
    }

    int rock = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++){
                if((chk[i][j][k]) || (space[i][j][k] != '*')) continue;
                dfs(i, j, k); rock++;
            }
        }
    }
    printf("%d\n", rock);

    return 0;
}