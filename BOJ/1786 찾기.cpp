#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long base = 256;
const long long MOD = 1e9 + 9;
string t, p;
long long tlen, plen;
int main(){
    getline(cin, t);
    getline(cin, p);
    tlen = t.length(); plen = p.length();

    vector<int> result;
    long long pattern = 0, str = 0, power = 1;
    for(int i = 0; i < plen; i++){
        pattern *= base;
        pattern %= MOD;
        pattern += p[i];
        pattern %= MOD;

        str *= base;
        str %= MOD;
        str += t[i];
        str %= MOD;
        if(i < plen - 1) {
            power *= base;
            power %= MOD;
        }
    }
    for(int i = 0; i <= tlen - plen; i++){
        if(pattern == str) result.push_back(i + 1);
        
        str = (((str - (t[i] * power) % MOD + MOD) % MOD * base) % MOD + t[i + plen]) % MOD;
    }
    cout << result.size() << "\n";
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    return 0;
}
//Rabin-Karp Algorithm