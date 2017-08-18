#include <stdio.h>
#include <algorithm>
using namespace std;
int mp[1001][1001];
int main(){
    int n, m, res = 0; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) scanf("%1d", &mp[i][j]);
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(!mp[i][j]) continue;
            mp[i][j] += min(mp[i - 1][j - 1], min(mp[i - 1][j], mp[i][j - 1]));
            res = max(res, mp[i][j]);
        }
    }
    printf("%d\n", res * res);
    return 0;
}