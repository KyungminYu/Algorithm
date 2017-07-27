#include <stdio.h>
int a[100001];
int main(){
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    int max = -1e9; int sum = 0;
    for(int i = 0; i < n; i++){
        if(sum < 0) sum = a[i];
        else sum += a[i];
        if(max < sum) max = sum;
    }
    printf("%d\n", max);
    return 0;
}