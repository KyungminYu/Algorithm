#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, int> > lines;
const int INF = 1e9 + 7;
int main(){
    int n, u, v;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d\n", &u, &v);
        lines.push_back(make_pair(u, v));
    }
    sort(lines.begin(), lines.end());
    int res = 0, l = -INF, r = -INF;
    for(int i = 0; i < lines.size(); i++){
        if(r < lines[i].first){
            res += (r - l);
            l = lines[i].first;
            r = lines[i].second;
        }
        else r = max(r, lines[i].second);
    }
    res += (r - l);
    printf("%d\n", res);
    return 0;
}