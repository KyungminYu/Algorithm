#include <stdio.h>
int in[100002], post[100001];
void printPre(int il, int ir, int pl, int pr){
    if(pr < pl) return;
    printf("%d ", post[pr]);
    printPre(il, in[post[pr]] - 1, pl, in[post[pr]] - 1 - il + pl);
    printPre(in[post[pr]] + 1, ir, in[post[pr]] - ir + pr, pr - 1);
}
int main(){
    int n, t; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &t), in[t] = i;
    for(int i = 0; i < n; i++) scanf("%d", &post[i]);
    printPre(0, n - 1, 0, n - 1);
    return 0;
}