#include <stdio.h>
#include <string>
#include <map>
using namespace std;

char s1[20], s2[20];
int parent[100001];
int count[100001];
int find(int v){
    if(v == parent[v]) return v;
    return parent[v] = find(parent[v]);
}
int Union(int u, int v){
    u = find(u); v = find(v);
    if(u != v){
        parent[v] = u;
        count[u] += count[v];
    }
    return count[u];
}
int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m; scanf("%d", &n);
        for(int i = 0; i <= 100000; i++) {
            parent[i] = i; count[i] = 1;
        }
        map<string, int> mp;
        m = 0;
        for(int i = 0; i < n; i++){
            scanf("%s %s", &s1, &s2);
            if(mp.find(s1) == mp.end()) mp[s1] = m++;
            if(mp.find(s2) == mp.end()) mp[s2] = m++;
            int cnt = Union(mp[s1], mp[s2]);
            printf("%d\n", cnt);
        }
    }
    return 0;
}