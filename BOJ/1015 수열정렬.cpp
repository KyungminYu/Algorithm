#include <stdio.h>
#include <algorithm>
using namespace std;

struct _pair{
	int val, ind;
	_pair(){};
	void read(int ind){
		this->ind = ind;
		scanf("%d", &val);
	}
	int operator < (_pair p) const{
		if(val == p.val) return ind < p.ind;
		return val < p.val;
	}
}A[51];
int B[51];
int main(){
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		A[i].read(i);
	sort(A, A + n);
	for(int i = 0; i < n; i++) B[A[i].ind] = i;
	for(int i = 0; i < n; i++) printf("%d ", B[i]);
	return 0;
}