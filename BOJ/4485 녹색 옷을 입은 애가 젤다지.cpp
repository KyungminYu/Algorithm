#include <stdio.h>
#include <queue>
using namespace std;
const short INF = 30000;
short T, n;
char mp[125][125];
short dist[125][125];
short dx[] = { 0, 0, 1, -1 };
short dy[] = { 1, -1, 0, 0 };
int isCan(short x, short y){
    if(0 <= x && x < n && 0 <= y && y < n) return 1;
    return 0;
}
int main(){
    while(1){
        scanf(" %hd", &n);
        if(n == 0) break;
        for(short i = 0; i < n; i++){
            for(short j = 0; j < n; j++){
                scanf(" %c", &mp[i][j]);
                dist[i][j] = INF;
            }
        }
        short sx, sy;
        sx = sy = 0;
        dist[sx][sy] = (short)(mp[sx][sy] - '0');
        priority_queue<pair<short, pair<short, short> > > pq;
        pq.push({-dist[sx][sy], {sx, sy}});
        while(!pq.empty()){
            short cx = pq.top().second.first;
            short cy = pq.top().second.second;
            pq.pop();
            for(int i = 0; i < 4; i++){
                short tx = cx + dx[i];
                short ty = cy + dy[i];
                if(!isCan(tx, ty)) continue;
                if(dist[cx][cy] + (short)(mp[tx][ty] - '0') < dist[tx][ty]){
                    dist[tx][ty] = dist[cx][cy] + (short)(mp[tx][ty] - '0');
                    pq.push({-dist[tx][ty], {tx, ty}});
                }
            }
        }
        printf("Problem %hd: %hd\n", ++T, dist[n - 1][n - 1]);
    }
    return 0;
}