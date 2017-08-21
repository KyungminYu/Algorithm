#pragma GCC optimize("O2")
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int fail[1000001];
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    string s, p;
    getline(cin, s);
    getline(cin, p);
    for(int i = 1, j = 0; i < p.length(); i++){
        while(j && p[i] != p[j]) j = fail[j - 1];
        if(p[i] == p[j]) fail[i] = ++j;
    }
    vector<int> res;
    for(int i = 0, j = 0; i < s.length(); i++){
        while(j && s[i] != p[j]) j = fail[j - 1];
        if(s[i] == p[j]){
            if(j == p.length() - 1){
                res.push_back(i - p.length() + 2);
                j = fail[j];
            }
            else j++;
        }
       
    }
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    return 0;
}