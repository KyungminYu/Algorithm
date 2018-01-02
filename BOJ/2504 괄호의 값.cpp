#include <stdio.h>
#include <string.h>
using namespace std;

char in[31];
int len, val, multi = 1, n, m;
int main(){
    scanf("%s", in);
    len = strlen(in);
    for(int i = 0; i < len; i++){
        if(in[i] == '('){
            n++;
            multi *= 2;
            if(in[i + 1] == ')') 
                val += multi;
        }
        else if(in[i] == '['){
            m++;
            multi *= 3;
            if(in[i + 1] == ']') 
                val += multi;
        }
        
        else if(in[i] == ')'){
            n--;
            multi /= 2;
        }
        else if(in[i] == ']'){
            m--;
            multi /= 3;
        }
    }
    if(n != 0 || m != 0) printf("0");
    else printf("%d", val);
    return 0;
}