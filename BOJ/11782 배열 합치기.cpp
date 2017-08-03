#include <stdio.h>
int a[1000001], b[1000001];
int main(){
    int i, n, m; scanf("%d %d", &n, &m);
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    for(i = 0; i < m; i++) scanf("%d", &b[i]);
    int aptr = 0, bptr = 0;
    while(aptr < n && bptr < m){
        if(a[aptr] < b[bptr]) printf("%d ", a[aptr++]);
        else printf("%d ", b[bptr++]);
    }    
    while(aptr < n)
        printf("%d ", a[aptr++]);
    while(bptr < m)
        printf("%d ", b[bptr++]);
    return 0;
}