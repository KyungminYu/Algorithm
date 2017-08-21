#pragma GCC optimize("O2")
#include <stdio.h>
using namespace std;

int fail[1000001], len;
char p[1000001];
int main(){
    while(1){
        scanf("%s", p);
        if(p[0] == '.') break;
        for(len = 0; p[len] != '\0'; len++) fail[len] = 0;
        for(int i = 1, j = 0; p[i] != '\0'; i++){
            while(j && p[i] != p[j]) j = fail[j - 1];
            if(p[i] == p[j]) fail[i] = ++j;
        }
        int pi = fail[len - 1];
        if(pi == 0 || len % (len - pi))printf("1\n");
        else printf("%d\n", len / (len - pi));
    }
    return 0;
}