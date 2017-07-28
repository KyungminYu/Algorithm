#include <stdio.h>
#include <vector>
using namespace std;

const long long MOD = 524287;
const long long base = 27;
char str[200001];
vector<int> pos[MOD];
int main(){
    int L; scanf("%d", &L);
        
    for(int i = 0; i < L; i++) scanf("%c", &str[i]);

    int low = 0, high = L, res = 0;
    while(low <= high){
        int mid = (low + high) / 2, dup = 0;
        //mid 길이의 문자열중에 두개 이상 나오는거 확인
        long long val = 0, power = 1;
        for(int i = 0; i < MOD; i++) pos[i].clear();
        for(int i = 0; i <= L - mid; i++){
            if (i == 0){
                for(int j = 0; j < mid; j++){
                    val *= base;
                    val += str[j];
                    val %= MOD;
                    if(j < mid - 1){
                        power *= base;
                        power %= MOD;   
                    }
                }
            }
            else val = (((val - (str[i - 1] * power) % MOD + MOD) % MOD * base) % MOD + str[i + mid - 1]) % MOD;
            if(pos[val].size()){
                for(auto p : pos[val]){
                    int compare = 1;
                    for(int j = 0; j < mid; j++){
                        if(str[i + j] != str[p + j]){
                            compare = 0;
                            break;
                        }
                    }   
                    if(compare){
                        dup = 1;
                        break;
                    }
                }
            }
            if(dup) break;
            else pos[val].push_back(i);
        }
        if(dup) {
            if(res < mid) res = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}