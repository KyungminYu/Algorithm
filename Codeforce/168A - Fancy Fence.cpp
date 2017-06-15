#include <stdio.h>
int main(){
    int n, a;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        if(!(360 % (180 - a)))  printf("YES\n");
        else                    printf("NO\n");
    }
    return 0;
}