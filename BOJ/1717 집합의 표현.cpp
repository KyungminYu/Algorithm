#include <stdio.h>
int set[1000001];
int find(int u){
    if(set[u] == u) return set[u];
    return set[u] = find(set[u]);
}
void Union(int u, int v){
    u = find(u); v = find(v);
    if(u != v) set[u] = v;
}
int main(){
    int n, m, q, a, b;
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= n; i++) set[i] = i;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &q, &a, &b);
        if(!q) Union(a, b);
        else{
            if(find(a) != find(b)) printf("NO\n");
            else printf("YES\n");
        }
    }

}