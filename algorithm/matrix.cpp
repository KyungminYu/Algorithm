#include <stdio.h>
#include <vector>
using namespace std;

typedef vector<vector<long long> > matrix;
const long long MOD = 1000;
matrix unit(long long n){
    matrix ret(n, vector<long long>(n));
    for (long long i = 0; i < n; i++) 
        ret[i][i] = 1;
    return ret;
}
matrix add(const matrix &a, const matrix &b){
    long long n, m;
    n = a.size(); m = a[0].size();
    matrix ret(n, vector<long long>(m));
    for (long long i = 0; i < n; i++){
        for (long long j = 0; j < m; j++) 
            ret[i][j] = (a[i][j] + b[i][j]) % MOD;
    }
    return ret;
}
matrix multi(const matrix &a, const matrix &b){
    long long n, m, k;
    n = a.size(); m = a[0].size(); k = b[0].size();
    matrix ret(n, vector<long long>(k));
    for (long long i = 0; i < n; i++){
        for (long long j = 0; j < k; j++){
            for (long long p = 0; p < m; p++){
                ret[i][j] += (long long)(a[i][p] * b[p][j]);
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}
matrix power(const matrix &a, long long p){
    matrix ret = unit(a.size());
    matrix tmp = a;
    long long i = 0;
    while(p){
        if(p & (1LL << i)){
            p -= (1LL << i);
            ret = multi(ret, tmp);
        }
        i++;
        tmp = multi(tmp, tmp);
    }
    return ret;
}

int main(){
    long long n, b;
    scanf("%lld %lld", &n, &b);
    matrix a(n, vector<long long>(n));
    for (long long i = 0; i < n; i++){
        for (long long j = 0; j < n; j++) scanf("%lld", &a[i][j]);
    }
    matrix res = power(a, b);
    for (long long i = 0; i < n; i++){
        for (long long j = 0; j < n; j++) printf("%lld ", res[i][j]);
        printf("\n");
    }
    return 0;
}