#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

int main(){
    stack<int> stk;
    vector<char> res;
    // until은 마지막으로 stack에 넣은 값 
    int n, until = 0;
    scanf("%d", &n);
    while(n--) {
        int val; scanf("%d", &val);
    	// val를 출력하기 위해서는 val가 stack에 있어야 한다.
    	// 따라서 val가 나올때까지 stack에 값을 넣어야 한다.
        if(until < val){
            for (int i = until; i < val; i++) {
                res.push_back('+');
                stk.push(i + 1);
            }
            until = val;
        }
        // 이미 val가 stack에 있을 경우 그 값이 top에 없으면
        // 문제가 있는 것이기 때문에 NO를 출력하고 종료한다.
        else if(stk.top() != val) {
            printf("NO\n");
            return 0;
        }
    	// stack의 top에 있는 val를 pop해준다.
        res.push_back('-');
        stk.pop(); 
    }
    for(char out : res)
        printf("%c\n", out);
    return 0;
}