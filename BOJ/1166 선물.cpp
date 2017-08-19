#include <stdio.h>
#include <algorithm>
using namespace std;
typedef unsigned long long llu;
int main(){
    llu n, l, w, h;
    scanf("%llu %llu %llu %llu", &n, &l, &w, &h);
    double res, left = 0, right = max(l, max(w, h));

    for(int i = 0; i < 1000; i++){
        double mid = (left + right) / 2;
        if(mid <= l && mid <= w && mid <= h
            && ((llu)(l / mid) * (llu)(w / mid) * (llu)(h / mid) >= n)){
            res = mid;
            left = mid;
        }
        else 
            right = mid;
    }
    printf("%.10lf\n", res);
    return 0;
}