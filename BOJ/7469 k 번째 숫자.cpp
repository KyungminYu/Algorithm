#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int mmax = 100005;
int Tree[mmax * 25], L[mmax * 25], R[mmax * 25], root[mmax], arr[mmax], recover[mmax];
vector<int> comp; 
int nxt = 0;
int get(vector<int> &comp, int x){
    return lower_bound(comp.begin(), comp.end(), x) - comp.begin() + 1;
}
int makeTree(int parent, int s, int e, int pos){
    if(pos < s || e < pos) return parent;
    int cur = ++nxt;
    if(s == e){
        Tree[cur] = Tree[parent] + 1;
        return cur;
    }
    int lt = makeTree(L[parent], s, (s + e) / 2, pos);
    int rt = makeTree(R[parent], (s + e) / 2 + 1, e, pos);
    Tree[cur] = Tree[lt] + Tree[rt];
    L[cur] = lt; R[cur] = rt;
    return cur;
}
int query(int a, int b, int s, int e, int kth){
    int cnt = Tree[L[b]] - Tree[L[a]];
    if(s == e) return s;
    if(kth <= cnt) return query(L[a], L[b], s, (s + e) / 2, kth);
    return query(R[a], R[b], (s + e) / 2 + 1, e, kth - cnt);
}
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &arr[i]);
        comp.push_back(arr[i]);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i = 1; i <= n; i++){
        int val = arr[i];
        arr[i] = get(comp, val);
        recover[arr[i]] = val;
    }
    root[0] = L[0] = R[0] = 0;
    for(int i = 1; i <= n; i++)
        root[i] = makeTree(root[i - 1], 1, comp.size(), arr[i]);
    
    for(int i = 1; i <= m; i++){
        int l, r, kth; scanf("%d %d %d", &l, &r, &kth);
        printf("%d\n", recover[query(root[l - 1], root[r], 1, comp.size(), kth)]);
    }
    return 0;
}