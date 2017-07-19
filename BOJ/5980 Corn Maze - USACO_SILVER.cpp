#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
char maze[301][301];
int dist[301][301];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int n, m;
pair<int, int> Exit;
vector<pair<int, int> > slide[26];
queue<pair<int, int> > q;
int isCan(int r, int c){
    if(0 <= r && r < n && 0 <= c && c < m && maze[r][c] != '#') return 1;
    return 0;
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf(" %c", &maze[i][j]);
            dist[i][j] = INF;
            if(maze[i][j] == '@') {
                q.push(make_pair(i, j));
                dist[i][j] = 0;
            }
            else if(maze[i][j] == '=') Exit = make_pair(i, j);
            else if('A' <= maze[i][j] && maze[i][j] <= 'Z') 
                slide[maze[i][j] - 'A'].push_back(make_pair(i, j));
        }
    }
    while(!q.empty()){
        int cr = q.front().first;
        int cc = q.front().second;
        int cst = dist[cr][cc];
        q.pop();
        if(Exit == make_pair(cr, cc)) {
            printf("%d\n", dist[cr][cc]);
            break;
        }
        for(int i = 0; i < 4; i++){
            int tr = cr + dr[i];
            int tc = cc + dc[i];
            if(!isCan(tr, tc)) continue;
            if((maze[tr][tc] == '.' || maze[tr][tc] == '=')){
                if(cst + 1 < dist[tr][tc]){
                    dist[tr][tc] = cst + 1;
                    q.push(make_pair(tr, tc));
                }
            }
            else if('A' <= maze[tr][tc] && maze[tr][tc] <= 'Z'){
                int sr, sc;
                if(slide[maze[tr][tc] - 'A'][0] == make_pair(tr, tc)){
                    sr = slide[maze[tr][tc] - 'A'][1].first;
                    sc = slide[maze[tr][tc] - 'A'][1].second;
                } 
                else{
                    sr = slide[maze[tr][tc] - 'A'][0].first;
                    sc = slide[maze[tr][tc] - 'A'][0].second;
                } 
                if(cst + 1 < dist[sr][sc]){
                    dist[sr][sc] = cst + 1;
                    q.push(make_pair(sr, sc));
                }
            }
        }
    }
    return 0;
}