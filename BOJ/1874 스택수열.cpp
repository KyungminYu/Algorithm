#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

stack<int> st;
vector<char> ans;
int main(){
    int n, cur, ind, max, i, j;
    scanf("%d", &n);
    cur = 1; max = 0;
    for(i = 0; i < n; i++) {
        scanf("%d", &ind);
        if(ind > max){
            for (j = max; j < ind; j++) {
                ans.push_back('+');
                st.push(j + 1);
            }
        }
        else if(st.top() != ind) break;
        ans.push_back('-');
        st.pop();
        if(max < ind) max = ind; 
    }
    if(i != n) printf("NO\n");
    else for(int i = 0; i < ans.size(); i++) printf("%c\n", ans[i]);
    return 0;
}