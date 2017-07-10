#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> G[2555];
int ecc[2555];
int chk[2555][2555];
int MIN, MAX, delu, delv, addu, addv;

void dfs(int v, int par, int depth, int blk, int &diameter, int &ind){
    if(ecc[v] <= depth) ecc[v] = depth;
    if(diameter < depth){
        diameter = depth;
        ind = v;
    }
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(nxt == par || nxt == blk) continue;
        dfs(nxt, v, depth + 1, blk, diameter, ind);
    }
}
void getCenter(int v, int par, int blk, int rad, int &ind){
    if(ecc[v] == rad) {
        ind = v;
        return;
    }
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i];
        if(nxt == par || nxt == blk) continue;
        getCenter(nxt, v, blk, rad, ind);
    }
}
pair<int, pair<int, int> > getDiametor(int v, int blk){
    int diameter, rad, ind, x, y;
    diameter = 0;
    x = y = v;
    dfs(v, -1, 0, blk, diameter, x);
    diameter = 0;
    dfs(x, -1, 0, blk, diameter, y);
    rad = diameter / 2;
    if(diameter % 2 == 1) rad++;
    getCenter(y, -1, blk, rad, ind);
    return make_pair(ind, make_pair(diameter, rad));
}
int main(){
    int n, u, v;
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++){
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    MIN = 1e9; MAX = -1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < G[i].size(); j++){
            //i to G[i][j]; 끊기
            if(chk[i][G[i][j]]) continue;
            memset(ecc, 0, sizeof(ecc)); 
            chk[i][G[i][j]] = chk[G[i][j]][i] = 1;
            pair<int, pair<int, int> > lval, rval;
            lval = getDiametor(i, G[i][j]);
            rval = getDiametor(G[i][j], i);

            MAX = max(lval.second.first, rval.second.first);
            MAX = max(MAX, lval.second.second + rval.second.second + 1);

            if(MAX < MIN){
                MIN = MAX;
                delu = i, delv = G[i][j];
                addu = lval.first; addv = rval.first;
            }
        }
    }
    printf("%d\n", MIN);
    printf("%d %d\n", delu, delv);
    printf("%d %d\n", addu, addv);

    return 0;
}