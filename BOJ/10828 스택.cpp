#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main(){
    int n; scanf("%d", &n);
    stack<int> stk;
    while(n--){
        char in[6]; scanf("%s", in);
        if(strcmp(in, "push") == 0){
            int val; scanf("%d", &val);
            stk.push(val);
        }
        else if(strcmp(in, "pop") == 0){
            if(stk.empty()) printf("-1\n");
            else {
                printf("%d\n", stk.top());
                stk.pop();
            }
        }
        else if(strcmp(in, "size") == 0)
            printf("%d\n", stk.size());
        else if(strcmp(in, "empty") == 0)
            printf("%d\n", stk.empty());
        else if(strcmp(in, "top") == 0){
            if(stk.empty()) printf("-1\n");
            else printf("%d\n", stk.top());
        }
    }
    return 0;
}