#include <stdio.h>
#include <map>
using namespace std;
map<int, int> mp;
int main(){
    int n, in; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &in);
        mp[in]++;
    }

    int m; scanf("%d", &m);
    for(int i = 0; i < m; i++){
        int s; scanf("%d", &s);
        printf("%d ", mp[s]);
    }
    return 0;
}