#include <stdio.h>
#include <queue>
using namespace std;

const int INF = 1e9;
int dist[1000001];
int main(){
    int F, S, G, U, D;
    scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
    for(int i = 1; i <= F; i++) dist[i] = INF;
    queue<int> q;
    q.push(S);
    dist[S] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        if(cur + U <= F && dist[cur] + 1 < dist[cur + U]) {
            dist[cur + U] = dist[cur] + 1;
            q.push(cur + U);
        }
        if(1 <= cur - D && dist[cur] + 1 < dist[cur - D]) {
            dist[cur - D] = dist[cur] + 1;
            q.push(cur - D);
        }
    }
    dist[G] == INF ? printf("use the stairs\n") : printf("%d\n", dist[G]) ;
    return 0;
}