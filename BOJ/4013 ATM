#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
const int NMAX = 500005;

vector<int> G[NMAX];
int has[NMAX], shas[NMAX], rest[NMAX], srest[NMAX];
int n, m, s, p;

int timer, SN;
int num[NMAX], fin[NMAX], sn[NMAX];
stack<int> S;

int indeg[NMAX], chk[NMAX];
vector<int> SG[NMAX];

int sMAX[NMAX];

int dfs(int v){
    num[v] = ++timer;
    S.push(v);

    int res = num[v];
    for(int nxt : G[v]){
        if(!num[nxt]) res = min(res, dfs(nxt));
        else if(!fin[nxt]) res = min(res, num[nxt]);
    }

    if(res == num[v]){
        while(1){
            int tmp = S.top();
            S.pop();
            fin[tmp] = 1;
            sn[tmp] = SN;
            if(tmp == v) break;
        }
        SN++;
    }
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v; scanf("%d %d", &u, &v);
        G[u].push_back(v);
    }
    for(int i = 1; i <= n; i++)
        scanf("%d", &has[i]);
    scanf("%d %d", &s, &p);
    for(int i = 0; i < p; i++){
    	int t; scanf("%d", &t);
    	rest[t] = 1;
    }

    for(int i = 1; i <= n; i++){
        if(num[i]) continue;
        dfs(i);
    }
    
    int sstart = sn[s];
    for(int i = 1; i <= n; i++){
    	shas[sn[i]] += has[i];
    	if(rest[i]) srest[sn[i]] = 1;
    	for(int j : G[i]){
    		if(sn[i] != sn[j]){
    			SG[sn[i]].push_back(sn[j]);
    			indeg[sn[j]]++;
    		}
    	}
    }
    queue<int> Q;
    for(int i = 0; i < SN; i++){
    	sMAX[i] = shas[i];
    	if(i == sstart) chk[i] = 1;
    	if(indeg[i] == 0) Q.push(i);
    }
    
    while(!Q.empty()){
    	int cur = Q.front();
    	Q.pop();
    	for(int nxt : SG[cur]){
    		if(chk[cur]){
    			sMAX[nxt] = max(sMAX[nxt], sMAX[cur] + shas[nxt]);
    			chk[nxt] = 1;
    		}
    		if(--indeg[nxt] == 0) Q.push(nxt);
    	}
    }
    int res = 0;
    for(int i = 0; i < SN; i++){
    	if(chk[i] && srest[i])
    		res = max(res, sMAX[i]);
    }
    printf("%d\n", res);
    return 0;
}
