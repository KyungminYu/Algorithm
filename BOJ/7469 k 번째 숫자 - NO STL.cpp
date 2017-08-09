#include <stdio.h>
const int mmax = 100005;
int Tree[mmax * 25], L[mmax * 25], R[mmax * 25];
int root[mmax], arr[mmax], comp[mmax], recover[mmax];
int nxt = 0;
int _lower_bound(int*A, int s, int e, int x){
    while(s < e){  
        int mid = (s + e) / 2;
        if(A[mid] < x) s = mid + 1;
        else e = mid;
    }
    return e + 1;
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
void merge(int* A, int s, int m, int e){
    int lptr = s, rptr = m + 1, ptr = s;
    int tmp[mmax];
    while(lptr <= m && rptr <= e){
        if(A[lptr] <= A[rptr]) tmp[ptr++] = A[lptr++];
        else tmp[ptr++] = A[rptr++];
    }
    while(lptr <= m)
        tmp[ptr++] = A[lptr++];
    while(rptr <= e)
        tmp[ptr++] = A[rptr++];
    for(int i = s; i <= e; i++)
        A[i] = tmp[i];
}
void msort(int* A, int s, int e){
    if(s >= e) return;
    int mid = (s + e) / 2;
    msort(A, s, mid);
    msort(A, mid + 1, e);
    merge(A, s, mid, e);
}
int erase(int* A, int s, int e){
    int len = 0;
    A[len++] = A[s];
    for(int i = s + 1; i < e; i++){
        if(A[len - 1] == A[i]) continue;
        A[len++] = A[i]; 
    }
    return len;
}
int main(){
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &arr[i]);
        comp[i - 1] = arr[i];
    }
    msort(comp, 0, n - 1);
    int len = erase(comp, 0, n);
    for(int i = 1; i <= n; i++){
        int val = arr[i];
        arr[i] = _lower_bound(comp, 0, len, val);
        recover[arr[i]] = val;
    }
    root[0] = L[0] = R[0] = 0;
    for(int i = 1; i <= n; i++)
        root[i] = makeTree(root[i - 1], 1, len, arr[i]);
    
    for(int i = 1; i <= m; i++){
        int l, r, kth; scanf("%d %d %d", &l, &r, &kth);
        printf("%d\n", recover[query(root[l - 1], root[r], 1, len, kth)]);
    }
    return 0;
}