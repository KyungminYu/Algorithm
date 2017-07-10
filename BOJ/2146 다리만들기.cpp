#include <stdio.h>
#include <queue>
using namespace std;
queue<pair<int, int> > q;
int mp[101][101], chk[101][101];
pair<int, int> dist[101][101];
int dr[] = { 0, 0 ,1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, MIN;
int isCan(int r, int c){
    if(0 <= r && r < n && 0 <= c && c < n) return 1;
    return 0;
}
void dfs(int r, int c, int nth){
    mp[r][c] = nth;
    chk[r][c] = 1;
    dist[r][c].first = 0;
    dist[r][c].second = nth; 
    int flag = 0;
    for(int i = 0; i < 4; i++){
        int tr = r + dr[i];
        int tc = c + dc[i];
        if(!isCan(tr, tc)) continue;
        if(mp[tr][tc] == 0) {
            flag = 1;
            continue;
        }
        if(chk[tr][tc]) continue;
        dfs(tr, tc, nth);
    }
    if(flag) q.push(make_pair(r, c));
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) scanf("%d", &mp[i][j]);
    }
    int nth = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mp[i][j] == 0) continue;
            if(chk[i][j]) continue;
            dfs(i, j, nth++);
        }
    }
    MIN = 1e9;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int tr = r + dr[i];
            int tc = c + dc[i];
            if(!isCan(tr, tc)) continue;
            if(dist[tr][tc].second == 0){
                dist[tr][tc].first = dist[r][c].first + 1;
                dist[tr][tc].second = dist[r][c].second;
                q.push(make_pair(tr, tc));
            }
            else if(dist[r][c].second != dist[tr][tc].second){
                if(dist[r][c].first + dist[tr][tc].first < MIN)
                    MIN = dist[r][c].first + dist[tr][tc].first;
            }
        }
    }
    printf("%d\n", MIN);
    return 0;
}