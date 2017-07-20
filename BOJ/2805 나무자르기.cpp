#include <stdio.h>
long long n, m, Mx; 
long long tree[1000001];
int main(){
    scanf("%lld %lld", &n, &m);
    for(long long i = 0;i < n; i++) {
        scanf("%lld", &tree[i]);
        if(Mx < tree[i]) Mx = tree[i];
    }
    long long l = 0, r = Mx;
    long long mid, sum, result = 0;
    while(l <= r){
        mid = (l + r) / 2, sum = 0;
        for(int i = 0; i < n; i++)
            if(mid < tree[i]) sum += (tree[i] - mid);
        if(m <= sum) {
            if(result < mid) result = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    printf("%lld\n", result);
    return 0;
}