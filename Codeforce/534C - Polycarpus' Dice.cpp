#include <stdio.h>
long long max(long long n1, long long n2){
    if(n1 > n2) return n1;
    return n2;
}
long long min(long long n1, long long n2){
    if(n1 < n2) return n1;
    return n2;
}
long long dice[200000];
int main(){
    long long n, A, sum = 0, mmax, mmin;
    scanf("%lld %lld", &n, &A);
    for(long long i = 0; i < n; i++){
        scanf("%lld", &dice[i]);
        sum += dice[i];
    }
    for(long long i = 0; i < n; i++){
        mmax = max(1LL, A - (sum - dice[i]));
        mmin = min(dice[i], A - (n - 1));
        printf("%lld ", dice[i] - (mmin - mmax + 1)); 
    }
    return 0;
}