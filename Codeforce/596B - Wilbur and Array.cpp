#include <stdio.h>
#include <stdlib.h>

int b[200001];
int main(){
    int n, i, sum = 0, cnt = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d", &b[i]);
    for(i = 0; i < n; i++){
        if(sum == b[i]) continue;
        cnt += abs(sum - b[i]);
        sum = b[i];
    }
    printf("%d\n", cnt);
    return 0;
}