#include <stdio.h>
int num, ans, minus = 1;
int main(){
    char s;
    while(scanf("%c", &s) != EOF){
        if('0' <= s && s <= '9') {
            num *= 10;
            num += (s - '0');
        }
        else{
            ans += minus * num;
            if(s == '-' && minus == 1) minus = -1;
            num = 0;
        }
    }
    ans += minus * num;
    printf("%d\n", ans);
    return 0;
}