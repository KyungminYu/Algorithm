#pragma GCC optimize("O2")
#include <stdio.h>
using namespace std;

int fail[1000001], n;
char s[2000001], p[1000001];
int GCD(int u, int v){
    int t;
    while (u){
        if (u < v){
            t = u; u = v; v = t;
        }
        u = u - v;
    }
    return v;
}
int main(){
    int n, res = 0; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf(" %c", &s[i]);
    for(int i = n; i < 2 * n - 1; i++) s[i] = s[i - n];
    for(int i = 0; i < n; i++) scanf(" %c", &p[i]);

    for(int i = 1, j = 0; i < n; i++){
        while(j && p[i] != p[j]) j = fail[j - 1];
        if(p[i] == p[j]) fail[i] = ++j;
    }

    for(int i = 0, j = 0; i < 2 * n - 1; i++){
        while(j && s[i] != p[j]) j = fail[j - 1];
        if(s[i] == p[j]){
            if(j == n - 1){
                res++;
                j = fail[j];
            }
            else j++;
        }
    }
    int gcd = GCD(n, res);
    printf("%d/%d\n", res/gcd, n/gcd);
    return 0;
}