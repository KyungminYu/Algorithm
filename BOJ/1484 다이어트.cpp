#include <stdio.h>
int main(){
    int G; scanf("%d", &G);
    int s, e, cnt = 0; 
    s = e = 1;
    while(s <= e){
        int val = e * e - s * s;
        if(s + 1 == e && G < val) break;
        if(G <= val) s++;
        else e++;
        if(val == G) {
            printf("%d\n", e);
            cnt++;
        }
    }
    if(!cnt) printf("-1\n");
    return 0;
}