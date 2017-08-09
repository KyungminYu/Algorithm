#include <stdio.h>
int n, m, q;
int info[3][1001][1001];
char mp[1001][1001];
int query(int ind, int r1, int c1, int r2, int c2){
    return info[ind][r2][c2] + info[ind][r1 - 1][c1 - 1]
         - info[ind][r2][c1 - 1] - info[ind][r1 - 1][c2];
}
int main(){
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf(" %c", &mp[i][j]);
            for(int k = 0; k < 3; k++)
                info[k][i][j] = info[k][i - 1][j] + info[k][i][j - 1] - info[k][i - 1][j - 1];
            if(mp[i][j] == 'J') info[0][i][j]++;
            if(mp[i][j] == 'O') info[1][i][j]++;
            if(mp[i][j] == 'I') info[2][i][j]++;
        }
    }
    for(int i = 0; i < q; i++){
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        printf("%d %d %d\n", query(0, r1, c1, r2, c2), 
            query(1, r1, c1, r2, c2), query(2, r1, c1, r2, c2));
    }
    return 0;
}