#include <stdio.h>
#include <vector>
using namespace std;

vector<int> tree[51];
int chk[51];
int n, root, d, cnt;
void dfs(int v){
    int flag = 1;
    chk[v] = 1;
    for(int i = 0; i < tree[v].size(); i++){
        int nxt = tree[v][i];
        if(chk[nxt]) continue;
        flag = 0;
        dfs(nxt);
    }
    if(flag) cnt++;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &d);
        if(d == - 1) root = i;
        else tree[d].push_back(i);
    }
    scanf("%d", &d);
    chk[d] = 1;
    if(root != d) dfs(root);
    printf("%d\n", cnt);
    return 0;
}