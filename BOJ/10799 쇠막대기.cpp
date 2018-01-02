#include <stdio.h>
#include <string.h>

char in[100005];
int main(){
    scanf("%s", in);
    int len = strlen(in), stksize = 0, res = 0;
    for(int i = 0; i < len;){
        if(in[i] == '(' && in[i + 1] == ')'){
            res += stksize;
            i += 2;
        }
        else {
            if(in[i] == '(') stksize++;
            else {
                res++;
                stksize--;
            }
            i++;
        }
    }
    printf("%d", res);
    return 0;
}