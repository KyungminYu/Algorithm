#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e17;
typedef struct{
    long long pos, dur, Cost, type;
}voucher;

vector<voucher> v;
long long minCost[200005];
long long ans;
int cmp(voucher v1, voucher v2){
    if(v1.pos == v2.pos)
        return v1.type < v2.type;
    return v1.pos < v2.pos;
}
int main(){
    long long n, x, l, r, c;
    scanf("%lld %lld", &n, &x);
    for(long long i = 0; i < n; i++){
        scanf("%lld %lld %lld", &l, &r, &c);
        v.push_back({l, r - l + 1, c, 0});
        v.push_back({r, r - l + 1, c, 1});
    }
    sort(v.begin(), v.end(), cmp);
    ans = INF;
    for(int i = 0; i < 200005; i++) minCost[i] = INF;
    for(int i = 0; i < v.size(); i++){
        if(v[i].type) minCost[v[i].dur] = min(minCost[v[i].dur], v[i].Cost);
        else if(0 < x - v[i].dur) ans = min(ans, minCost[x - v[i].dur] + v[i].Cost);
    }
    printf("%lld\n", ans == INF ? -1LL : ans);
    return 0;
}