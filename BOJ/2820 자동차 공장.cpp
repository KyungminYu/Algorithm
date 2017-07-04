#include <stdio.h>
#include <vector>
using namespace std;

vector<int> tree[500001];
int pre[500001], post[500001];
long long income[500001];
long long ftree[1 << 19];

long long sum(int i) {
    long long ans = 0;
    while (i > 0) {
        ans += ftree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(int i, long long num, int n) {
    while (i <= n) {
        ftree[i] += num;
        i += (i & -i);
    }
}
void dfs(int v, int parent, int& num){
    pre[v] = ++num;
    for(int i = 0; i < tree[v].size(); i++){
        int nxt = tree[v][i];
        if(nxt == parent) continue;
        dfs(nxt, v, num );
    }
    post[v] = num;
}
int main(){
    int n, m, p;
    scanf("%d %d %lld", &n, &m, &income[1]);
    for(int i = 2; i <= n; i++){
        scanf(" %d %lld", &income[i], &p);
        tree[p].push_back(i);
    }

    int num = 0;
    dfs(1, -1, num);

    int a;
    long long x;
    char order;
    for(int i = 0; i < m; i++){
        scanf(" %c", &order);
        if(order == 'p'){
            scanf(" %d %lld", &a, &x);
            update(pre[a] + 1, x, n);
            update(post[a] + 1, -x, n);
        }
        else if(order == 'u'){
            scanf(" %d", &a);
            printf("%lld\n", income[a] + sum(pre[a]));
        }
    }
    return 0;
}