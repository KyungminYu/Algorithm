#include <stdio.h>
#include <math.h>
int main(){
    while(1){
        int n; scanf("%d", &n);
        if(n == 0) break;
        int pi = 1;
        int tmp = n;
        for(int i = 2; i * i <= tmp; i++){
            int cnt = 0;
            if(tmp % i == 0){
                while(!(tmp % i)) {
                    tmp /= i;
                    cnt++;
                }
            }
            if(cnt == 0) continue;
            pi *= (i - 1) * pow(i, cnt - 1);
        }
        if(tmp > 1) pi *= (tmp - 1);
        printf("%d\n", pi);
    }
    return 0;
}