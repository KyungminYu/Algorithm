#include <stdio.h>

long long tree[4000000];
void update(int n, int s, int e, int ind, long long diff) {
    if (ind < s || ind > e) return;
    tree[n] += diff;
    if (s != e) {
        update(n * 2, s, (s + e) / 2, ind, diff);
        update(n * 2 + 1, (s + e) / 2 + 1, e, ind, diff);
    }
}
long long sum(int n, int s, int e, int l, int r) {
    if (l > e || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    return sum(n * 2, s, (s + e) / 2, l, r) + sum(n * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
int main(){
    int n, q, order, p, x;
    scanf("%d %d", &n, &q);
    for(int i = 0; i < q; i++){
        scanf("%d %d %d", &order, &p, &x);
        if(order == 1) update(1, 1, n, p, x);
        else printf("%lld\n", sum(1, 1, n, p, x));
    }
    return 0;
}
