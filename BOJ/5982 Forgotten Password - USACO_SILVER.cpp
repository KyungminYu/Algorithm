#include <iostream>
#include <string>
using namespace std;

string p, dic[1001], dp[1001];
int l, nw;
int match(int dpInd, int dicInd){
    for(int i = 0; i < dic[dicInd].length(); i++){
        if(p[i + dpInd] == '?') continue;
        if(p[i + dpInd] != dic[dicInd][i]) return 0;
    }
    return 1;
}
int main(){
    cin >> l >> nw >> p;
    for(int i = 0; i < nw; i++) cin >> dic[i];
    for(int i = l - 1; i >= 0; i--){
        for(int j = 0; j < nw; j++){
            int range = i + dic[j].length();
            if(l < range) continue;
            if(!match(i, j)) continue;
            if(range != l && dp[range] == "") continue;
            if(dp[i] == "" || dp[i] > dic[j] + dp[range])
                dp[i] = dic[j] + dp[range];
        }   
    }
    cout << dp[0] << "\n";
    return 0;
}