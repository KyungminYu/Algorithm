#include <stdio.h>
#include <vector>
using namespace std;
vector<int> primeSet;
int prime[1000001];
int main(){
    for(int i = 2; i <= 1000000; i++) prime[i] = 1;
    for(int i = 2; i <= 1000000; i++){
        if(prime[i]){
            for(int j = i * 2; j <= 1000000; j += i)
                prime[j] = 0;
            primeSet.push_back(i);
        }
    }
    while(1){
        int n, i; scanf("%d", &n);
        if(n == 0) break;
        for(i = 0; primeSet[i] <= n; i++){
            if(prime[n - primeSet[i]]){
                printf("%d = %d + %d\n", n, primeSet[i], n - primeSet[i]);
                break;
            }
        } 
        if(i == n) printf("Goldbach's conjecture is wrong.\n");
    }
    return 0;
}