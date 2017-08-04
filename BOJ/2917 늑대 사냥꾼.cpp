#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

const int INF = 1e9;
int dist[500][500];
int chk[500][500];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
queue<pair<int, int> > tree;
int n, m, low, high, mid, ans;
int pr, pc, jr, jc;
char mp;
int isCan(int r, int c){
    if(0 <= r && r < n && 0 <= c && c < m) return 1;
    return 0;
}

void dfs(int r, int c, int val){
    if(dist[r][c] < val) return;
    chk[r][c] = 1;
    for(int i = 0; i < 4; i++){
        int tr = r + dr[i];
        int tc = c + dc[i];
        if(!isCan(tr, tc)) continue;
        if(chk[tr][tc]) continue;
        if(dist[tr][tc] >= val) dfs(tr, tc, val);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j =0; j < m; j++) {
            scanf(" %c", &mp);
            dist[i][j] = INF;
            if(mp == '+') {
                dist[i][j] = 0;
                tree.push({i, j});
            }
            else if(mp == 'V') pr = i, pc = j;
            else if(mp == 'J') jr = i, jc = j;
        }
    }

    while(!tree.empty()){
        int r = tree.front().first;
        int c = tree.front().second;
        tree.pop();
        for(int i = 0; i < 4; i++){
            int tr = r + dr[i];
            int tc = c + dc[i];
            if(!isCan(tr, tc)) continue;
            if(dist[r][c] + 1 < dist[tr][tc]){
                dist[tr][tc] = dist[r][c] + 1;
                if(high < dist[tr][tc]) high = dist[tr][tc];
                tree.push({tr, tc});
            }
        }
    }
    ans = -1;
    while(low <= high){
        mid = (low + high) / 2;
        memset(chk, 0, sizeof(chk));
        dfs(pr, pc, mid);
        if(chk[jr][jc]) {
            ans = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}