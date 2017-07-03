#include <stdio.h>
#include <set>
#include <iterator>
using namespace std;
#define MAX(X,Y) (X > Y ? X : Y)

/*
이진 탐색 트리의 속성
집어넣는 값의 depth는 
해당 값 바로 직전의 노드의 depth와 직후의 노드의 depth의 최대값을 가진다.
1 2 3 4 5 6 7 8 
- - 1 - - - - - 
- - 1 - 2 - - - 
2 - 1 - 2 - - - 
2 - 1 - 2 3 - - 
2 - 1 - 2 3 - 4 
2 - 1 - 2 3 5 4 
2 3 1 - 2 3 5 4 
2 3 1 3 2 3 5 4 
위의 특징을 이용해서 depth를 빠르게 구할 수 있다.
set이라는 자료구조는 binary search를 이용하기 때문에 
한번 search에 log n 만큼 걸림
n개의 원소에 대해서 매번 search하기 때문에 nlog n만큼 걸림 
*/

set<int> SET;
set<int>::iterator it;
int n, NODE, tree[300002];
long long c;
int main(){
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