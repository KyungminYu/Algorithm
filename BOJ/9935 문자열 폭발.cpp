#include <stdio.h>
#include <string.h>
using namespace std;

char str[1000001], ans[1000001], bomb[37];
int cmp(int ind, int len){
    if(ind < 0) return 0;
    for(int i = 0; i < len; i++){
        if(ans[ind + i] != bomb[i]) return 0;
    }
    return 1;
}
int main(){
    scanf("%s %s", &str, &bomb);
    int inlen, blen;
    inlen = strlen(str);
    blen = strlen(bomb);
    int ind = 0;
    for(int i = 0; i <= inlen; i++){
        if(cmp(ind - blen, blen)) ind -= blen;
        ans[ind++] = str[i];
    }
    ans[ind] = '\0';
    if(!ans[0]) printf("FRULA\n");
    else printf("%s\n", ans);
    return 0;
}
//FRULA