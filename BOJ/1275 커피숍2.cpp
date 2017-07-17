#include <stdio.h>
#define swap(a, b){int t = a; a = b; b = t;}
long long tree[400004], arr[100001];
void update(int n, int s, int e, int ind, long long diff) {
    if (ind < s || ind > e) return;
    tree[n] += diff;
    if (s != e) {
        int mid = (s + e) / 2;
        update(n * 2, s, mid, ind, diff);
        update(n * 2 + 1, mid + 1, e, ind, diff);
    }
}
long long sum(int n, int s, int e, int l, int r) {
    if (l > e || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    int mid = (s + e) / 2;
    return sum(n * 2, s, mid, l, r) + sum(n * 2 + 1, mid + 1, e, l, r);
}
int main(){
    int n, q;
    long long x, y, a, b;
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        update(1, 1, n, i, arr[i]);
    }
    for(int i = 0; i < q; i++){
        scanf("%lld %lld %lld %lld", &x, &y, &a, &b);
        if(x > y) swap(x, y);
        printf("%lld\n", sum(1, 1, n, x, y));
        long long diff = b - arr[a];
        arr[a] = b;
        update(1, 1, n, a, diff);        
    }
    return 0;
}
