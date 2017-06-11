#include <stdio.h>
using namespace std;

int M[2200][2200];
int ans[3];
int val(int N, int Sx, int Sy){
    int ret = M[Sx][Sy];
    for(int i = Sx;i<Sx+N;i++){
        for(int j = Sy; j<Sy+N;j++)
            if(ret != M[i][j]) return -2;
    }
    ans[ret+1]++;
    return ret;
}
void DnC(int N, int Sx, int Sy){
    if(val(N, Sx, Sy) != -2) return;
    DnC(N/3, Sx, Sy);
    DnC(N/3, Sx, Sy + N / 3);
    DnC(N/3, Sx, Sy + 2 * N / 3);
    DnC(N/3, Sx + N / 3, Sy);
    DnC(N/3, Sx + N / 3, Sy + N / 3);
    DnC(N/3, Sx + N / 3, Sy + 2 * N / 3);
    DnC(N/3, Sx + 2 * N / 3, Sy);
    DnC(N/3, Sx + 2 * N / 3, Sy + N / 3);
    DnC(N/3, Sx + 2 * N / 3, Sy + 2 * N / 3);
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0 ;i < n; i++){
        for(int j = 0 ;j < n; j ++)
            scanf("%d", &M[i][j]);
    }
    DnC(n, 0, 0);
    printf("%d\n%d\n%d\n", ans[0], ans[1], ans[2]);
    return 0;
}