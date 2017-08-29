#pragma GCC optimize("O2")
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
struct Ball{int rr, rc, br, bc;};
char mp[11][11];
int chk[11][11][11][11];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int n, m, srr, src, sbr, sbc, fr, fc;
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf(" %c", &mp[i][j]);
            if(mp[i][j] == 'R')      srr = i, src = j;
            else if(mp[i][j] == 'B') sbr = i, sbc = j;
            else if(mp[i][j] == 'O') fr  = i, fc  = j;
        }
    }
    queue<Ball> q;
    q.push({ srr, src, sbr, sbc });
    chk[srr][src][sbr][sbc] = 1;
    int res = -1, depth = 0;
    while(!q.empty()){
        int size = q.size();
        while(size--){
            int rr = q.front().rr;
            int rc = q.front().rc;
            int br = q.front().br;
            int bc = q.front().bc;
            q.pop();
            if(mp[rr][rc] == 'O' && (mp[rr][rc] != mp[br][bc])) {
                res = depth;
                break;
            }
            for(int i = 0; i < 4; i++){
                int trr = rr, trc = rc, tbr = br, tbc = bc;
                while(mp[trr + dr[i]][trc + dc[i]] != '#' && mp[trr][trc] != 'O') trr += dr[i], trc += dc[i];
                while(mp[tbr + dr[i]][tbc + dc[i]] != '#' && mp[tbr][tbc] != 'O') tbr += dr[i], tbc += dc[i];
                if(trr == tbr && trc == tbc) {
                    if(mp[trr][trc] == 'O') continue;
                    if (abs(trr - rr) + abs(trc - rc) < abs(tbr - br) + abs(tbc - bc)) tbr -= dr[i], tbc -= dc[i];
                    else trr -= dr[i], trc -= dc[i];
                }
                if(chk[trr][trc][tbr][tbc]) continue;
                q.push({trr, trc, tbr, tbc});
                chk[trr][trc][tbr][tbc] = 1;
            }
        }
        if(depth++ >= 10) break;
        if(res != -1) break;
    }
    printf("%d\n", res);
    return 0;
}