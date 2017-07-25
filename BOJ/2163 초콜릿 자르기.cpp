#include <stdio.h>
int main(){ 
    int n, m; 
    scanf("%d %d", &n, &m);
    printf("%d\n", (m - 1) + m * (n - 1));
    return 0;
}