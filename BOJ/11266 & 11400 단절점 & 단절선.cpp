#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int> > G[100001];
struct Edge{
    int ind, u, v;
    void read(int ind){
        scanf("%d %d", &u, &v);
        if(u > v) swap(u, v);
        this->ind = ind;
        G[u].push_back(make_pair(v, ind));
        G[v].push_back(make_pair(u, ind));
    }
} edges[1000001];
int dfn[100001], low[100001], par[100001];
int isBridge[1000001], isAp[100001];
int timer;

void dfs(int v, int root){
    int cnt = 0;
    dfn[v] = low[v] = ++timer;
    for(int i = 0; i < G[v].size(); i++){
        int nxt = G[v][i].first;
        int ind = G[v][i].second;
        if(dfn[nxt] != 0){
            if(nxt != par[v]) low[v] = min(low[v], dfn[nxt]);
        }
        else{
            par[nxt] = v;
            dfs(nxt, root);
            cnt++;
            //if(low[nxt] > dfn[v]) isBridge[ind] = 1;
            if(low[nxt] >= dfn[v]) isAp[v] = 1;
            low[v] = min(low[v], low[nxt]);
        }
    }
    if(v == root) isAp[v] = cnt >= 2;
}

int main(){
    int v, e;
    scanf("%d %d", &v, &e);
    for(int i = 1; i <= e; i++){
        edges[i].read(i);
    }

    for(int i = 1; i <= v; i++){
        if(!dfn[i]) dfs(i, i);
    }

    //vector<pair<int, int> > bridge;
    vector<int> ap;
    /*for(int i = 1; i <= e; i++){
        if(isBridge[i]) bridge.push_back(make_pair(edges[i].u, edges[i].v));
    }*/
    for(int i = 1; i <= v; i++){
        if(isAp[i]) ap.push_back(i);
    }
    sort(ap.begin(), ap.end());
    /*sort(bridge.begin(), bridge.end());
    printf("%d\n", bridge.size());
    for(int i = 0; i < bridge.size(); i++) 
        printf("%d %d\n", bridge[i].first, bridge[i].second);*/
    printf("%d\n", ap.size());
    for(int i = 0; i < ap.size(); i++) 
        printf("%d ", ap[i]);
    return 0;
}