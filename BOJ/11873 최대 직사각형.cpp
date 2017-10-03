#pragma GCC optimize("O2")
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
vector<int> A;
vector<int> tree;

int mp[1001][1001];
void init(int n, int s, int e){
	if (s == e) {
		tree[n] = s;
		return;
	}
	init(n * 2, s, (s + e) / 2);
	init(n * 2 + 1, (s + e) / 2 + 1, e);
	if (A[tree[n * 2]] < A[tree[n * 2 + 1]]) 
		tree[n] = tree[n * 2];
	else tree[n] = tree[n * 2 + 1];
}

int query(int n, int s, int e, int i, int j) {
	if (i > e || j < s) return -1;
	if (i <= s && e <= j) return tree[n];
	
	int m1 = query(2 * n, s, (s + e) / 2, i, j);
	int m2 = query(2 * n + 1, (s + e) / 2 + 1, e, i, j);
	
	if (m1 == -1) return m2;
	else if (m2 == -1) return m1;
	else{
		if (A[m1] <= A[m2]) return m1;
		else return m2;
	}
}
int  Area(int s, int e){
	int n = A.size();
	int m = query(1, 0, n - 1, s, e);
	int area = (e - s + 1) * A[m];
	if (s <= m - 1)	area = max(area, Area(s, m - 1));
	if (m + 1 <= e)	area = max(area, Area(m + 1, e));
	return area;
}

int main(){
	while(1){
		int n, m; scanf("%d %d", &n, &m);
		if(n == 0 && m == 0) break;
		memset(mp, 0, sizeof(mp));
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				int val; scanf("%d", &val);
				if(val == 0) continue;
				mp[i][j] = mp[i - 1][j] + val;	
			} 
		}
		int ans = 0;
		for(int i = 1; i <= n; i++){
			A.resize(m);
			tree.resize(m * 4);
			for (int j = 0; j < m; j++) 
				A[j] = mp[i][j + 1];
			
			init(1, 0, m - 1);
			ans = max(ans, Area(0, m - 1));
			A.clear();
			tree.clear();
		}
		printf("%d\n", ans);
	}
	return 0;
}
