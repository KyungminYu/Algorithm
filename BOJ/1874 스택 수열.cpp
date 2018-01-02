#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

int main(){
    stack<int> stk;
    vector<char> res;
    // until�� ���������� stack�� ���� �� 
    int n, until = 0;
    scanf("%d", &n);
    while(n--) {
        int val; scanf("%d", &val);
    	// val�� ����ϱ� ���ؼ��� val�� stack�� �־�� �Ѵ�.
    	// ���� val�� ���ö����� stack�� ���� �־�� �Ѵ�.
        if(until < val){
            for (int i = until; i < val; i++) {
                res.push_back('+');
                stk.push(i + 1);
            }
            until = val;
        }
        // �̹� val�� stack�� ���� ��� �� ���� top�� ������
        // ������ �ִ� ���̱� ������ NO�� ����ϰ� �����Ѵ�.
        else if(stk.top() != val) {
            printf("NO\n");
            return 0;
        }
    	// stack�� top�� �ִ� val�� pop���ش�.
        res.push_back('-');
        stk.pop(); 
    }
    for(char out : res)
        printf("%c\n", out);
    return 0;
}