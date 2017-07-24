#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;
struct levelbyWidth{
    int mmin, mmax, depth;
};
pair<int, int> T[10001];
levelbyWidth l[10001];
int chk[10001];
int nth;
int cmp(levelbyWidth l1, levelbyWidth l2){
    if(l1.mmax - l1.mmin == l2.mmax - l2.mmin){
        if(l1.depth < l2.depth) return 1;
        return 0;
    }
    if(l1.mmax - l1.mmin > l2.mmax - l2.mmin) return 1;
    return 0;
}
void dfs(int v, int d){
    if(T[v].first != -1) dfs(T[v].first, d + 1);
    nth++;
    l[d].mmin = min(l[d].mmin, nth);
    l[d].mmax = max(l[d].mmax, nth);
    if(T[v].second != -1) dfs(T[v].second, d + 1);
}
int main(){
    int n, r, u, v; scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d %d", &r, &u, &v);
        T[r] = {u, v};
        if(u != -1) chk[u] = 1;
        if(v != -1) chk[v] = 1;
        l[r] = {INF, -INF, r};
    }
    int root;
    for(int i = 1; i <= n; i++){
        if(chk[i] == 0) {
            root = i;
            break;
        }
    }
    dfs(root, 1);
    sort(l + 1, l + n + 1, cmp);
    printf("%d %d \n", l[1].depth, l[1].mmax - l[1].mmin + 1);
    return 0;
}