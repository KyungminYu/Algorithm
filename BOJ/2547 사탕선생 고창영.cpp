#include <stdio.h>

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        unsigned long long N, sum = 0; 
        scanf("%llu", &N);
        for(long long i = 0; i < N; i++){
            unsigned long long in; 
            scanf("%llu", &in);
            in %= N;
            sum = (sum + in) % N;
        }
        if(!(sum % N)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}