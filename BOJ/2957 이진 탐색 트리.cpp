#include <stdio.h>
#include <set>
#include <iterator>
using namespace std;
#define MAX(X,Y) (X > Y ? X : Y)

set<int> SET;
set<int>::iterator it;
int n, NODE, tree[300002];
long long c;
int main(){
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	tree[0] = tree[n + 1] = -1;
	SET.insert(0);
	SET.insert(n + 1);

	for(int i = 0; i < n; i++){
		scanf("%d", &NODE);
		SET.insert(NODE);
		it = SET.find(NODE);
		it--;
		tree[NODE] = tree[*it];
		it++; it++;
		tree[NODE] = MAX(tree[NODE], tree[*it]) + 1;
		c += tree[NODE];
		printf("%lld\n", c); 
	}

	return 0;
}