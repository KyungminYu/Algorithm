#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

//S = 1/2(sigma i = 1 to n (xi + x(i + 1)) * (yi - y(i + 1)))
vector<pair<long long, long long> > P;
long long scale(int ind1, int ind2){
    return (P[ind1].first + P[ind2].first) * (P[ind1].second - P[ind2].second);
}
int main(){
    int n;
    long long p1, p2;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%lld %lld", &p1, &p2);
        P.push_back(make_pair(p1, p2));
    }
    P.push_back(P[0]);
    long long area = 0;
    for(int i = 0; i < n; i++)
        area += scale(i, i + 1);
    
    printf("%.1lf\n", llabs(area) / 2.0);
    return 0;
}