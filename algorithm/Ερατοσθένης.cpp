#include <stdio.h>
int prime[1000001];
int main(){
    for(int i = 2; i <= 1000000; i++) prime[i] = 1;
    for(int i = 2; i <= 1000000; i++){
        if(prime[i]){
            for(int j = i * 2; j <= 1000000; j += i)
                prime[j] = 0;
        }
    }
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = n; i <= m; i++)
        if(prime[i])printf("%d\n", i);
    return 0;
}