#include <stdio.h>
#include <vector>
using namespace std;

int paper[2200][2200];
int cnt[3];
int dx[] = {0, 0, 0, 1, 1, 1, 2, 2, 2 };
int dy[] = {0, 1, 2, 0, 1, 2, 0, 1, 2 };
int chk(int x, int y, int N){
    int base = paper[x][y];
    for(int i = x; i < x + N; i++){
        for(int j = y; j < y + N; j++)
            if(base != paper[i][j]) return 0;
    }
    return 1;
}
void DnC(int x, int y, int ind, int N){
    if(N == 1 || chk(x, y, N)){
        cnt[paper[x][y] + 1]++;
        return;
    }
    for(int i = 0; i < 9; i++)
        DnC(x + dx[i] * N / 3, y + dy[i] * N / 3, i, N / 3);
}   

int main(){
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n ; j++)
            scanf("%d", &paper[i][j]);
    }
    DnC(0, 0, 0, n);
    for(int i = 0; i < 3; i++) printf("%d\n", cnt[i]);
    return 0;
}