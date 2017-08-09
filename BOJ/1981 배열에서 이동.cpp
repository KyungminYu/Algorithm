#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int mp[101][101];
int chk[101][101];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, low, high, ans;
int isCan(int r, int c){ return (0 <= r && r < n && 0 <= c && c < n);}
int solve(int diff){
    for(int i = low; i <= high; i++){
        memset(chk, 0, sizeof(chk));
        for(int r = 0; r < n; r++){
            for(int c = 0; c < n; c++){
                if(i <= mp[r][c] && mp[r][c] <= i + diff)
                    chk[r][c] = 1;
            }
        }
        if(!chk[0][0]) continue;
        queue<pair<int, int> > q;
        q.push({0, 0});
        chk[0][0] = 0;
        while(!q.empty()){
            int cr = q.front().first;
            int cc = q.front().second;
            q.pop();
            if(cr == n - 1 && cc == n - 1) return 1;
            for(int d = 0; d < 4; d++){
                int tr = cr + dr[d];
                int tc = cc + dc[d];
                if(!isCan(tr, tc)) continue;
                if(!chk[tr][tc]) continue;
                chk[tr][tc] = 0;
                q.push({tr, tc});
            }
        }
    }
    return 0;
}
int main(){
    scanf("%d", &n);
    low = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            scanf("%d", &mp[i][j]);
            low  = min(low,  mp[i][j]);
            high = max(high, mp[i][j]);
        }
    }
    int start = 0, end = high, ans;
    while(start <= end){
        int mid = (start + end) / 2;
        if(solve(mid)) {
            ans = mid;
            end = mid - 1;
        }
        else start = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}