#pragma GCC optimize("O2")
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> tree, haybale, pos;
vector<pair<int, int> > q;

void update(int pos,int add){
    for(int i = pos; i < tree.size(); i += i&-i)
        tree[i] += add;
}
int sum(int pos){
    int ret = 0;
    for(int i = pos; i > 0; i -= i&-i)
        ret += tree[i];
    return ret;
}
int query(int l, int r){
    return sum(r) - sum(l - 1);
}

int getID(int val){
	return lower_bound(pos.begin(), pos.end(),val) - pos.begin() + 1;
}

int main(){
	int n, m; scanf("%d %d", &n, &m);
	tree.resize(n * 4);
	for(int i = 0; i < n; i++){
		int p; scanf("%d", &p);
		haybale.push_back(p);
		pos.push_back(p);
	}

	for(int i = 0; i < m; i++){
		int a, b; scanf("%d %d", &a, &b);
		q.push_back({a, b});
		pos.push_back(a); pos.push_back(b);
	}
	sort(pos.begin(), pos.end());
	pos.erase(unique(pos.begin(), pos.end()), pos.end());

	for(int i = 0; i < n; i++)
		update(getID(haybale[i]), 1);
	
	for(int i = 0; i < m; i++)
		printf("%d\n", query(getID(q[i].first), getID(q[i].second)));
	return 0;
}