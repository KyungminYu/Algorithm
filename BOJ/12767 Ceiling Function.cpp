#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<set<int>, int> mp;
pair<int, int> tree[1 << 20 + 1];
int main(){
    int n, k; scanf("%d %d", &n, &k);
    int node, root, cnt = 0;
    for(int i = 0; i < n; i++){
        memset(tree, 0, sizeof(tree));
        scanf("%d", &root);
        set<int> st;
        for(int j = 1; j < k; j++){
            scanf("%d", &node);
            int cur = root;
            int finind = 1;
            while(1){
                if(cur < node){
                    finind = finind * 2 + 1;
                    if(tree[cur].second != 0) cur = tree[cur].second;
                    else{
                        tree[cur].second = node;
                        break;
                    }
                }
                else{
                    finind = finind * 2;
                    if (tree[cur].first != 0) cur = tree[cur].first;
                    else {
                        tree[cur].first = node;
                        break;
                    }
                }
            }
            st.insert(finind);
        }
        if(mp.find(st) == mp.end()) mp[st] = cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}