#include <stdio.h>
#include <algorithm>
using namespace std;

int down[100000], up[100000];

int _lower_bound(int* A, int s, int e, int x){
    while(s < e){  
        int mid = (s + e) / 2;
        if(A[mid] < x) s = mid + 1;
        else e = mid;
    }
    return e;
}
int main(){
    int n, h;
    scanf("%d %d", &n, &h);
    n /= 2;
    for(int i = 0; i < n; i++)
        scanf("%d %d", &down[i], &up[i]);

    sort(down, down + n);
    sort(up,   up   + n);

    int mmin = 1e9, count = 0;
    for(int i = 1; i <= h; i++){
        int tmp = n - _lower_bound(down, 0, n, i) 
                + n - _lower_bound(up, 0, n, h - i + 1);
        if(mmin == tmp) count++;
        else if(mmin > tmp){
            mmin = tmp;
            count = 1;
        }
    }
    printf("%d %d\n", mmin, count);
    return 0;
}