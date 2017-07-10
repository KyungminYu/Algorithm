#include <stdio.h>
#include <vector>
using namespace std;
const long long MOD = 1000000007LL;
long long n, A, B, W, ANS;
vector<pair<long long, long long> > T[100001];

long long dfs(long long v, long long pre){
    long long ret = 1;
    for(long long i = 0; i < T[v].size(); i++){
        long long nxt = T[v][i].first;
        long long cost = T[v][i].second;
        if(nxt == pre) continue;
        long long tmp = dfs(nxt, v) * cost % MOD;
        ANS = (ANS + tmp * ret) % MOD;
        ret = (ret + tmp) % MOD;
    }
    return ret;
}
int main(){
    scanf("%d", &n);
    for(long long i = 0; i < n - 1; i++){
        scanf("%lld %lld %lld", &A, &B, &W);
        T[A].push_back(make_pair(B, W));
        T[B].push_back(make_pair(A, W));
    }
    if(n == 1) {
        printf("0\n");
        return 0;
    }
    dfs(1, -1);
    printf("%lld\n", ANS);
    return 0;
}