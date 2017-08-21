#pragma GCC optimize("O2")
#include <stdio.h>
using namespace std;
int fail[1000001], L;
char p[1000001];
int main(){
    scanf("%d %s", &L, p);
    for(int i = 0; i < L; i++) fail[L] = 0;
    for(int i = 1, j = 0; i < L; i++){
        while(j && p[i] != p[j]) j = fail[j - 1];
        if(p[i] == p[j]) fail[i] = ++j;
    }
    printf("%d\n", L - fail[L - 1]);
    return 0;
}