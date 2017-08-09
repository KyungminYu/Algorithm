#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
long long sum, num;
vector<long long> po, ne;
int main(){
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%lld", &num);
        if(num == 1) sum++;
        else if(num > 1) po.push_back(num);
        else ne.push_back(num);
    }
    sort(po.begin(), po.end());
    sort(ne.begin(), ne.end());
    int pind = po.size() - 1;
    while(0 <= pind){
        if(0 < pind) sum += po[pind--] * po[pind--];
        else sum += po[pind--];
    }
    int nind = 0;
    while(nind < ne.size()){
        if(nind <= ne.size() - 2) sum += ne[nind++] * ne[nind++];
        else sum += ne[nind++];
    }
    printf("%lld\n", sum);
    return 0;
}