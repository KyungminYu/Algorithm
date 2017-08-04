#include <stdio.h>
#include <map>
using namespace std;
const long long base = 27;
const long long mod1 = 1e9 + 7, mod2 = 1e9 + 9;
char str[1001][1001];
long long H1[1001], H2[1001];
long long pow1[1001], pow2[1001];
int main(){
    int r, c; scanf("%d %d", &r, &c);
    pow1[0] = pow2[0] = 1;
    for(int i = 0; i < r; i++){
        scanf("%s", &str[i]);
        pow1[i + 1] = (pow1[i] * base) % mod1;
        pow2[i + 1] = (pow2[i] * base) % mod2;
    }

    for(int i = 0; i < c; i++){
        for(int j = 0; j < r; j++){
            H1[i] = (H1[i] + ((str[j][i] - 'a' + 1) * pow1[r - j - 1]) % mod1) % mod1;
            H2[i] = (H2[i] + ((str[j][i] - 'a' + 1) * pow2[r - j - 1]) % mod2) % mod2;
        }
    }

    int ans = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            H1[j] = (H1[j] + mod1 - ((str[i][j] - 'a' + 1) * pow1[r - i - 1]) % mod1) % mod1;
            H2[j] = (H2[j] + mod2 - ((str[i][j] - 'a' + 1) * pow2[r - i - 1]) % mod2) % mod2;
        }

        map<long long, int> mp1, mp2;
        int dup = 0;
        for(int j = 0; j < c; j++){
            mp1[H1[j]]++;
            mp2[H2[j]]++;
            if(mp1[H1[j]] >= 2 && mp2[H2[j]] >= 2){
                dup = 1;
                break;
            }
        }
        if(dup) break;
        ans++;
    }
    printf("%d\n", ans);
    return 0;
}