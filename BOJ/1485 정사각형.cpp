#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int innerProduct(pair<int, int> v1, pair<int, int> v2){
    return v1.first * v2.first + v1.second * v2.second;
}
int dist(pair<int, int> p1, pair<int, int> p2){
    return (p1.first - p2.first) * (p1.first - p2.first) 
    + (p1.second - p2.second) * (p1.second - p2.second);
}
int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        pair<int, int> p[4], v[2];
        for(int i = 0; i < 4; i++) 
        	scanf("%d %d", &p[i].first, &p[i].second);
        v[0].first  = p[0].first  - p[1].first;
        v[0].second = p[0].second - p[1].second;
        v[1].first  = p[2].first  - p[3].first;
        v[1].second = p[2].second - p[3].second;
        if(dist(p[0], p[1]) == dist(p[2], p[3]) 
        	&& innerProduct(v[0], v[1]) == 0) {
        	printf("1\n");
        	continue;
        }
    
        v[0].first  = p[0].first  - p[2].first;
        v[0].second = p[0].second - p[2].second;
        v[1].first  = p[1].first  - p[3].first;
        v[1].second = p[1].second - p[3].second;
        if(dist(p[0], p[2]) == dist(p[1], p[3]) 
        	&& innerProduct(v[0], v[1]) == 0) {
        	printf("1\n");
        	continue;
        }
        
        v[0].first  = p[0].first  - p[3].first;
        v[0].second = p[0].second - p[3].second;
        v[1].first  = p[2].first  - p[1].first;
        v[1].second = p[2].second - p[1].second;
        if(dist(p[0], p[3]) == dist(p[2], p[1]) 
        	&& innerProduct(v[0], v[1]) == 0) {
        	printf("1\n");
        	continue;
        }
        printf("0\n");
    }
    return 0;
}