#include <stdio.h>
#include <string.h>
const long long mod = 1e9 + 7;
struct matrix{
    long long R[101][101];
    int n;
    matrix(int n, long long init){
        memset(R, 0, sizeof(R));
        this->n = n;
        for(int i = 0; i < n; i++) R[i][i] = init;
    }
    matrix operator *(matrix &mat){
        matrix ret(n, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++)
                    ret.R[i][j] = (ret.R[i][j] + R[i][k] * mat.R[k][j]) % mod;
            }
        }
        return ret;
    }
    matrix operator ^(int p){
        int i = 0;
        matrix ret(n, 1);
        matrix mul = *this;
        while(p){
            if(p & (1 << i)){
                p -= (1 << i);
                ret = ret * mul;
            }
            i++;
            mul = mul * mul;
        }
        return ret;
    }
};

long long cnt[10];
int main(){
    int n, b, k, x, a;
    scanf("%d %d %d %d", &n, &b, &k, &x);
    matrix mat(x, 0);
    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        cnt[a]++;
    }
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++){
            for(int d = 0; d < 10; d++){
                if((i * 10 + d) % x == j)
                    mat.R[i][j] += cnt[d];
            }
        }
    }
    mat = mat ^ b;
    printf("%lld\n", mat.R[0][k]);
    return 0;
}