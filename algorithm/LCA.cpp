#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;
const int MAXN=400001;
int parent[MAXN][20]={0,};  //버텍스 개수가 50만보다 크면 20보다 큰수로 해야함
int depth[MAXN]={0, };
vector<int> adj[MAXN];
void dfs(int here, int dad, int d){
    depth[here]=d;
    parent[here][0]=dad;
    for(auto there:adj[here]){
        if(there == dad)continue;
        dfs(there, here, d+1);
    }
}
int getLca(int u, int v)
{
    if(depth[u]>depth[v])swap(u, v);
    int d=depth[v]-depth[u];
    int i=0;
    while(d){
        if(d&(1<<i)){
            d-=(1<<i);
            v=parent[v][i];
        }
        i++;
    }
    if(u == v)return u;
    for(int i=19; i >= 0; i--){
        if(parent[u][i]!=parent[v][i])u=parent[u][i], v=parent[v][i];
    }
    return parent[u][0];
}

int getDist(int u, int v){
    return depth[u]+depth[v]-2*depth[getLca(u, v)]; //두정점 사이의 거리 구하기 o(logN)
}
int main(){
    int n;
    scanf("%d",&n);
    memset(parent,-1,sizeof(parent));
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1, 0); //
    for(int i=1; i<20; i++){
        for(int j=1; j <= n; j++){  //n == 정점수 알아서 선언하고 초기화해주기
            if(parent[j][i-1] <0)parent[j][i]=-1;
            else{
                parent[j][i]=parent[parent[j][i-1]][i-1];
            }
        }
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",getLca(a,b));
    }
    
    
    return 0;
}