#include <stdio.h>
#include <stack>
using namespace std;

int main(){
    int n; scanf("%d", &n);
    stack<pair<int, int> > stk;
    for(int i = 1; i <= n; i++){
        int val; scanf("%d", &val);
        while(!stk.empty()){
            if(stk.top().first > val){
                printf("%d ", stk.top().second);
                break;
            }
            stk.pop();
        }
        if(stk.empty()) printf("0 ");
        stk.push({val, i});
    }
    return 0;
}