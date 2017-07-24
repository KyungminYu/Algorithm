#include <stdio.h>
#include <vector>
using namespace std;

//typedef vector<vector<long long> > matrix;
#define matrix vector<vector<long long> >
const long long MOD = 1000000007;
matrix unit(long long n){
    matrix ret(n, vector<long long>(n));
    for (long long i = 0; i < n; i++) 
        ret[i][i] = 1;
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
    long long n; scanf("%lld", &n);
    matrix m(2, vector<long long>(2));
    m[0][0] = m[1][0] = m[0][1] = 1;
    matrix p = power(m, n);
    printf("%lld\n", p[0][1]);
    return 0;
}