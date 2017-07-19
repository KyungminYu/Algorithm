#include <stdio.h>
int chair[251];
int chk[251];
int main(){
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) chair[i] = i;
    int cur = 1, move = 1, nxt;
    chair[cur] = 0;
    chk[cur] = 1;
    while(1){
        nxt = (cur + move) % n;
        if(nxt == 0) nxt = n;
        if(chair[nxt] == 0) break;
        if(chk[chair[nxt]]) break;  
        move = chair[nxt];
        cur = nxt;
        chair[move] = move;
        chk[move] = 1;
    }
    printf("%d\n", cur);
    return 0;
}