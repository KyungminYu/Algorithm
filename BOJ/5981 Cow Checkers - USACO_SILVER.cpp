#include <stdio.h>
#include <string.h>
#define swap(a, b){int t = a; a = b; b = t;}
int lose[1616225];
int main(){
    int N, M, T; scanf("%d %d %d", &N, &M, &T);
    int x_axis = 0, y_axis = 0;
    memset(lose, -1, sizeof(lose));
    lose[x_axis] = y_axis;
    if(N < M) swap(N, M);
    while(1) {
        x_axis++; y_axis += 2;
        while(x_axis < N && lose[x_axis] != -1) { x_axis++; y_axis++; }
        if(x_axis >= N) break;
        lose[x_axis] = y_axis;
        if(y_axis < M) lose[y_axis] = x_axis;
    }
    for(int t = 0; t < T; t++){
        int X, Y; scanf("%d %d", &X, &Y);
        if(X > Y) swap(X, Y);
        if(lose[X] == Y) printf("Farmer John\n");
        else printf("Bessie\n");
    }
    return 0;
}