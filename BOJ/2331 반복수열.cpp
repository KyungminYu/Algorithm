#include <stdio.h>

int arr[1000001];
int chk[1000001];
int ans;
int nxtEle(int num, int p){
    int ret = 0;
    while(num){
        int m = num % 10;
        num/=10;
        int mult = 1;
        for(int i = 0; i < p; i++) mult *= m;
        ret += mult;
    }
    return ret;
}
void trav(int v){
    if(chk[v] == 0) return;
    ans++;
    trav(arr[v]);
}
int main(){
    int a, p;
    scanf("%d %d", &a, &p);
    int s = a;
    chk[a] = 1;
    while(1){
        int nxt = nxtEle(a, p);
        if(chk[nxt]){
            chk[nxt] = 0;
            break;
        }
        chk[nxt] = 1;
        arr[a] = nxt;
        a = nxt;
    }
    trav(s);
    printf("%d\n", ans);
    return 0;
}