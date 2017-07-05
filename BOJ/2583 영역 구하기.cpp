#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

/*
일반적인 DFS가 아니라 격자상에서 DFS를 사용할 수 있는 문제
DFS시 방문 여부 뿐 아니라 격자를 벗어나는지 체크해야함
DFS함수의 반환형이 void가 아니라 int형으로 1회 DFS했을 때 탐색한 vertex 수를 반환 하게 함

격자 문제에서는 x, y혹은 row, col의 순서를 잘 확인하고 코딩해야 함
*/

int map[101][101];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
vector<int> ans;
int isCan(int y, int x, int n, int m){
    if (0 <= x && x < m && 0 <= y && y < n) return 1;
    return 0;
}
int dfs(int y, int x, int n, int m){
    int ret = 1;
    map[y][x] = 1;
    for (int i = 0; i < 4; i++){
        int ty = y + dy[i];
        int tx = x + dx[i];
        if (!isCan(ty, tx, n, m)) continue;
        if (map[ty][tx]) continue;
        ret += dfs(ty, tx, n, m);
    }
    return ret;
}
int main(){
    int n, m, k, x1, y1, x2, y2;
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int j = y1; j < y2; j++) for (int k = x1; k < x2; k++) map[j][k] = 1;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (map[i][j]) continue;
            ans.push_back(dfs(i, j, n, m));
        }
    }
    printf("%d\n", ans.size());
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);

    return 0;
}