#include <stdio.h>
int jump;
void solve(int a, int b, int c){
    if(b - a == 1 && c - b == 1)return;
    jump++;
    if(b - a > c - b) solve(a, b - 1, b);
    else solve(b, b + 1, c);
}
int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    solve(a, b, c);
    printf("%d\n", jump);
    return 0;
}