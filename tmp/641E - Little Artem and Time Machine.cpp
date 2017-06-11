#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;

typedef struct QUERY{
   int ind, a, t, x;
}QUERY;
typedef struct TREE{
   map<int, int> sum;
}TREE;
int n, compress;
QUERY q[100001];
TREE tree[400004];
bool t_cmp(QUERY q1, QUERY q2){ return q1.t < q2.t; }
bool i_cmp(QUERY q1, QUERY q2){ return q1.ind < q2.ind; }
void update(int node, int s, int e, int time, int val, int diff){
   if (time < s || time > e) return;
   tree[node].sum[val] += diff;
   if (s != e){
      update(node * 2, s, (s + e) / 2, time, val, diff);
      update(node * 2 + 1, (s + e) / 2 + 1, e, time, val, diff);
   }
}
int query(int node, int s, int e, int l, int r, int val){
   if (l > e || r < s) return 0;
   if (l <= s && e <= r) return tree[node].sum[val];
   return query(node * 2, s, (s + e) / 2, l, r, val)
      + query(node * 2 + 1, (s + e) / 2 + 1, e, l, r, val);
}
int main(){
   freopen("input.txt", "r", stdin);
   compress = 1;
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
      q[i].ind = i;
      scanf("%d %d %d", &q[i].a, &q[i].t, &q[i].x);
   }
   sort(q, q + n, t_cmp);
   for (int i = 1; i <= n; i++) {
      if (q[i].t == q[i - 1].t) q[i - 1].t = compress;
      else q[i - 1].t = compress++;
   }
   sort(q, q + n, i_cmp);
   for (int i = 0; i < n; i++){
      if (q[i].a == 1)
         update(1, 1, n, q[i].t, q[i].x, 1);
      else if (q[i].a == 2)
         update(1, 1, n, q[i].t, q[i].x, -1);
      else
         printf("%d\n", query(1, 1, n, 1, q[i].t, q[i].x));
   }
   return 0;
}