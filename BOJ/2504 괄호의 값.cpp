#include <stdio.h>
#include <string.h>
using namespace std;

char str[31];
int mul, sum, n, m, len;
int main(){
    scanf("%s", &str);
    mul = 1;
    sum = n = m = 0;
    len = strlen(str);
    for(int i = 0; i < len; i++){
        if(str[i] == '('){
            n++; 
            mul *= 2;
            if(str[i + 1] == ')') sum += mul;
        }
        else if(str[i] == '['){
            m++; 
            mul *= 3;
            if(str[i + 1] == ']') sum += mul;
        }
        else if(str[i] == ')'){
            n--; 
            mul /= 2;
        }
        else if(str[i] == ']'){
            m--; 
            mul /= 3;
        }
    }
    if(n != 0 || m != 0) sum = 0;
    printf("%d\n", sum);
    return 0;
}