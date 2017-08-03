#include <stdio.h>
#include <algorithm>
#include <stack>
using namespace std;
int H[100001];
int main(){
    int n, scale = 0; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &H[i]);

    stack<int> idx;
    int l, r, Height, Width;
    for(int i = 0; i < n; i++){
        r = i;
        while(!idx.empty() && H[idx.top()] > H[i]){
            Height = H[idx.top()];
            idx.pop();
            if(idx.empty()) Width = r;
            else Width = r - idx.top() - 1;
            scale = max(scale, Width * Height);
        }
        idx.push(i);
    }
    while(!idx.empty()){
        Height = H[idx.top()];
        idx.pop();
        if(idx.empty()) Width = n;
        else Width = n - idx.top() - 1;
        scale = max(scale, Width * Height);
    }
    printf("%d\n", scale);
    return 0;
}