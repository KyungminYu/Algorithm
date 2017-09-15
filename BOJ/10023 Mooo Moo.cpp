#include <stdio.h>
const int INF = 0X3F3F3F3F;
int n, b;
int knap[100001], volume[21], sound[101];
int main() {
    scanf("%d %d", &n, &b);
    for (int i = 1; i <= b; i++) scanf("%d", &volume[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &sound[i]);

    knap[0] = 0;
    for (int i = 1; i <= 100000; i++) knap[i] = INF;
    for (int i = 1; i <= 100000; i++) {
        for (int j = 1; j <= b; j++) {
            int bef = i - volume[j];
            if (bef < 0 || knap[bef] > 1E9) continue;
            knap[i] = knap[i] < (knap[bef] + 1) ? knap[i] : (knap[bef] + 1);
        }
    }

    int move = 0, res = 0;
    for (int i = 1; i <= n; i++) {
        move = (move - 1) > 0 ? (move - 1) : 0;
        int v = sound[i] - move;
        res += knap[v];
        move = sound[i];
    }
    if (res > 1E9) res = -1;
    printf("%d\n", res);
    return res;
};