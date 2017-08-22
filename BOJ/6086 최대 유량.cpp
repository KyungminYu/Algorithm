#pragma GCC optimize("O2")
#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MMAX = 52;
vector<int> G[MMAX];
int flow[MMAX][MMAX], capacity[MMAX][MMAX];

int getID(char c){
    if(c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}
int main(){
    int n; scanf(" %d", &n);
    for(int i = 0; i < n; i++){
        char from, to; int cap;
        scanf(" %c %c %d", &from, &to, &cap);
        from = getID(from); 
        to = getID(to);
        capacity[from][to] += cap;
        G[from].push_back(to);
        G[to].push_back(from);
    }

    int totalflow = 0;
    int source = getID('A'), sink = getID('Z');

    while(1){
        int prev[MMAX];
        memset(prev, -1, sizeof(prev));
        queue<int> q;
        q.push(source);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < G[cur].size(); i++){
                int nxt = G[cur][i];
                if(capacity[cur][nxt] - flow[cur][nxt] > 0 
                    && prev[nxt] == -1){
                    q.push(nxt);
                    prev[nxt] = cur;
                    if(nxt == sink) break;  
                }
            }
        }

        if(prev[sink] == -1) break;

        int minFlow = INF;
        for(int i = sink; i != source; i = prev[i])
            minFlow = min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i]);
        for(int i = sink; i != source; i = prev[i]){
            flow[prev[i]][i] += minFlow;
            flow[i][prev[i]] -= minFlow;
        }
        totalflow += minFlow;
    }
    printf("%d\n", totalflow);
    return 0;
}