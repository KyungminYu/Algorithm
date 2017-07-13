#include <stdio.h>

int main(){
    long long a, b, c, ind, ret;
    scanf("%lld %lld %lld", &a, &b, &c);
    ret = 1;ind = 0;
    while(b){
        if(b & (1 << ind)){
            b -= (1 << ind);
            ret *= a;
            ret %= c;
        }
        a *= a;
        a %= c;
        ind++;
    }
    printf("%lld\n", ret);
    return 0;
}