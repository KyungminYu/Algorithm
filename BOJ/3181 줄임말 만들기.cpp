#include<iostream>
#include<string>
#include<sstream>
using namespace std;
string str[10] = { "i", "pa", "te", "ni", "niti", "a", "ali", "nego", "no", "ili" };
int main(){
    string s; getline(cin, s);
    stringstream tok(s);
    tok >> s;
    char out = s[0] - 'a' + 'A';
    cout << out;
    while (tok >> s){
        int chk = 0;
        for (int i = 0; i < 10; i++) {
            if (s == str[i]) {
			    chk = 1;
			    break;
            }
        }
        if(chk) continue;
        char out = s[0] - 'a' + 'A';
        cout << out;
    }
    return 0;
}