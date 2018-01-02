#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

char in[51];
int main(){
    int t; scanf("%d", &t);
    while(t--){
        scanf("%s", in);
        int len = strlen(in), chk = 0;
        stack<char> stk;
        for(int i = 0; i < len; i++){
            if(in[i] == ')'){
                if(stk.empty()){
                    chk = 1;
                    break;
                } 
                stk.pop();
            }
            else stk.push(in[i]);
        }
        if(chk || !stk.empty()) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}