#include <stdio.h>
int chess[6][6];
int isCan(int sx, int sy, int ex, int ey){
    if(((sx + 1 == ex || sx - 1 == ex) && (sy + 2 == ey || sy - 2 == ey))
        ||((sx + 2 == ex || sx - 2 == ex) && (sy + 1 == ey || sy - 1 == ey))) return 1;
    return 0;
}
int main(){
    char in[3];
    int sx, sy, tx, ty;
    scanf("%s", &in);
    sx = tx = in[0] - 'A'; sy = ty = in[1] - '1';

    if(tx < 0 || 6 <= tx || ty < 0 || 6 <= ty) {
        printf("Invalid\n");
        return 0;
    }
    chess[tx][ty] = 1;
    for(int i = 0; i < 35; i++){
        scanf("%s", &in);
        int x = in[0] - 'A', y = in[1] - '1';
        if(x < 0 || 6 <= x || y < 0 || 6 <= y) {
            printf("Invalid\n");
            return 0;
        }
        if(chess[x][y] || !isCan(tx, ty, x, y)) {
            printf("Invalid\n");
            return 0;
        }
        chess[x][y] = 1;
        tx = x; ty = y; 
    }
    for(int i = 0; i < 6; i++){
        for(int j =0; j < 6; j++){
            if(!chess[i][j]){
                printf("Invalid\n");
                return 0;      
            }
        }
    }
    if(isCan(tx, ty, sx, sy)) printf("Valid\n");
    else printf("Invalid\n");
    return 0;
}