#include <stdio.h>
#include <vector>
using namespace std;
int memo[1024], k;
vector<int> depth[11];
void search(int l, int r, int d){
    if(l == r || d == k) {
        depth[d].push_back(memo[l]);
        return;
    }
    int mid = (l + r) / 2;
    depth[d].push_back(memo[mid]);
    search(l, mid - 1, d + 1);
    search(mid + 1, r, d + 1);
}
int main(){
    scanf("%d", &k);
    for(int i = 0; i < (1 << k); i++) 
        scanf("%d", &memo[i]);
    int l = 0, r = (1 << k) - 1;
    search(l, r, 0);
    for(int i = 0; i < k; i++){
        for(int j = 0; j < depth[i].size(); j++)
            printf("%d ", depth[i][j]);
        printf("\n");
    }
    return 0;
}